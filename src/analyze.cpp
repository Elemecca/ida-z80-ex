/* -----BEGIN COPYRIGHT NOTICE-----
 * Copyright 2017 Sam Hanes
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not, see
 *   http://www.gnu.org/licenses/
 * -----END COPYRIGHT NOTICE-----
 */


#include "module.hpp"
#include "registers.hpp"
#include "instructions.hpp"


static const uint16 table_reg[] = {
    z80r_b,
    z80r_c,
    z80r_d,
    z80r_e,
    z80r_h,
    z80r_l,
    z80r_hl,
    z80r_a
};

static inline void decode_reg(op_t &op, uint8 val) {
    op.reg = table_reg[val];
    op.type = (z80r_hl == op.reg ? o_phrase : o_reg);
}


static const uint16 table_pair[] = {
    z80r_bc,
    z80r_de,
    z80r_hl,
    z80r_sp
};

static inline void decode_pair(op_t &op, uint8 val) {
    op.type = o_reg;
    op.reg = table_pair[val];
}


static inline void decode_n(insn_t &inst, op_t &op) {
    op.type = o_imm;
    op.dtype = dt_byte;
    op.value = inst.get_next_byte();
}

static inline void decode_nn(insn_t &inst, op_t &op) {
    op.type = o_imm;
    op.dtype = dt_word;
    op.value = inst.get_next_word();
}

// only works when the offset is the final operand
static inline void decode_relative(insn_t &inst, op_t &op) {
    int8 offset = inst.get_next_byte();
    op.type = o_near;
    op.addr = inst.ip + inst.size + offset;
}



int z80_analyze(insn_t &inst) {
    uint8 opcode = inst.get_next_byte();

    //  7 6 5 4 3 2 1 0
    // | x |  y  |  z  |
    //     | p |q|
    uint8 x = opcode & 0xC0 >> 6;
    uint8 y = opcode & 0x38 >> 3;
    uint8 z = opcode & 0x07;
    uint8 p = y & 0x6 >> 2;
    uint8 q = y & 0x1;

    switch (x) {
    case 0: // x0
        switch (z) {
        case 0: // x0 z0
            switch (y) {
            case 0: // x0 z0 y0
                inst.itype = z80i_nop;
                return inst.size;

            case 1: // x0 z0 y1
                inst.itype = z80i_exaf;
                return inst.size;

            case 2: // x0 z0 y2
                inst.itype = z80i_djnz;
                decode_relative(inst, inst.ops[0]);
                return inst.size;

            case 3: // x0 z0 y3
                inst.itype = z80i_jr;
                decode_relative(inst, inst.ops[0]);
                return inst.size;

            default: // x0 z0 y4..7
                inst.itype = z80i_jrcc;
                inst.ops[0].type = o_cond;
                inst.ops[0].reg = y - 4;
                decode_relative(inst, inst.ops[1]);
                return inst.size;
            }
            break;

        case 1: // x0 z1
            if (1 == q) { // x0 z1 q1
                inst.itype = z80i_add;
                inst.ops[0].type = o_reg;
                inst.ops[0].reg = z80r_hl;
                decode_pair(inst.ops[1], p);
                return inst.size;
            } else { // x0 z1 q0
                inst.itype = z80i_ld;
                decode_pair(inst.ops[0], p);
                decode_nn(inst, inst.ops[1]);
                return inst.size;
            }
            break;

        case 2: // x0 z2
            {   inst.itype = z80i_ld;
                op_t &op1 = inst.ops[q ? 1 : 0];
                op_t &op2 = inst.ops[q ? 0 : 1];

                if (p & 2) { // x0 z2 p2..3
                    op1.type = o_mem;
                    op1.addr = inst.get_next_word();
                    op2.type = o_reg;
                    op2.reg  = (p & 1 ? z80r_a : z80r_hl);
                } else { // x0 z2 p0..1
                    op1.type = o_reg;
                    op1.reg  = (p & 1 ? z80r_de : z80r_bc);
                    op2.type = o_reg;
                    op2.reg  = z80r_a;
                }
            }
            return inst.size;

        case 3: // x0 z3
            inst.itype = (q ? z80i_dec : z80i_inc);
            decode_pair(inst.ops[0], p);
            return inst.size;

        case 4: // x0 z4
            inst.itype = z80i_inc;
            decode_reg(inst.ops[0], y);
            return inst.size;

        case 5: // x0 z5
            inst.itype = z80i_dec;
            decode_reg(inst.ops[0], y);
            return inst.size;

        case 6: // x0 z6
            inst.itype = z80i_ld;
            decode_reg(inst.ops[0], y);
            decode_n(inst, inst.ops[1]);
            return inst.size;

        case 7: // x0 z7
            // table as consecutive enum values
            inst.itype = z80i_rlca + y;
            return inst.size;
        }
        break;

    case 1: // x1
        if (6 == y && 6 == z) {
            inst.itype = z80i_halt;
            return inst.size;
        } else {
            inst.itype = z80i_ld;
            decode_reg(inst.ops[0], y);
            decode_reg(inst.ops[1], z);
            return inst.size;
        }
        break;

    case 2: // x2
        // table as consecutive enum values
        inst.itype = z80i_add + y;
        inst.ops[0].type = o_reg;
        inst.ops[0].reg = z80r_a;
        decode_reg(inst.ops[1], z);
        return inst.size;

    case 3: // x3
        switch (z) {
        case 0: // x3 z0
            inst.itype = z80i_retcc;
            inst.ops[0].type = o_cond;
            inst.ops[0].reg = y;
            return inst.size;

        case 1: // x3 z1
            if (!q) { // x3 z1 q0
                inst.itype = z80i_pop;
                decode_pair(inst.ops[0], p);
                if (z80r_sp == inst.ops[0].reg) {
                    inst.ops[0].reg = z80r_af;
                }
                return inst.size;
            } else { // x3 z1 q1
                switch (p) {
                case 0: // x3 z1 q1 p0
                    inst.itype = z80i_ret;
                    return inst.size;

                case 1: // x3 z1 q1 p1
                    inst.itype = z80i_exx;
                    return inst.size;

                case 2: // x3 z1 q1 p2
                    inst.itype = z80i_jp;
                    inst.ops[0].type = o_reg;
                    inst.ops[0].reg  = z80r_hl;
                    return inst.size;

                case 3: // x3 z1 q1 p3
                    inst.itype = z80i_ld;
                    inst.ops[0].type = o_reg;
                    inst.ops[0].reg  = z80r_sp;
                    inst.ops[1].type = o_reg;
                    inst.ops[1].reg  = z80r_hl;
                    return inst.size;
                }
            }
            break;

        case 2: // x3 z2
            inst.itype = z80i_jpcc;
            inst.ops[0].type = o_cond;
            inst.ops[0].reg  = y;
            inst.ops[1].type = o_near;
            inst.ops[1].addr = inst.get_next_word();
            return inst.size;

        case 3: // x3 z3
            switch (y) {
            case 0: // x3 z3 y0
                inst.itype = z80i_jp;
                inst.ops[0].type = o_near;
                inst.ops[1].addr = inst.get_next_word();
                return inst.size;

            case 1: // x3 z3 y1
                // 0xCB prefix
                break;

            case 2: // x3 z3 y2
                inst.itype = z80i_out;
                inst.ops[0].type = o_mem;
                inst.ops[0].addr = inst.get_next_byte();
                inst.ops[1].type = o_reg;
                inst.ops[1].reg  = z80r_a;
                return inst.size;

            case 3: // x3 z3 y3
                inst.itype = z80i_in;
                inst.ops[0].type = o_reg;
                inst.ops[0].reg  = z80r_a;
                inst.ops[1].type = o_mem;
                inst.ops[1].addr = inst.get_next_byte();
                return inst.size;

            case 4: // x3 z3 y4
                inst.itype = z80i_ex;
                inst.ops[0].type = o_phrase;
                inst.ops[0].reg  = z80r_sp;
                inst.ops[1].type = o_reg;
                inst.ops[1].reg  = z80r_hl;
                return inst.size;

            case 5: // x3 z3 y5
                inst.itype = z80i_ex;
                inst.ops[0].type = o_reg;
                inst.ops[0].reg  = z80r_de;
                inst.ops[1].type = o_reg;
                inst.ops[1].reg  = z80r_hl;
                return inst.size;

            case 6: // x3 z3 y6
                inst.itype = z80i_di;
                return inst.size;

            case 7: // x3 z3 y7
                inst.itype = z80i_ei;
                return inst.size;
            }
            break;

        case 4: // x3 z4
            inst.itype = z80i_callcc;
            inst.ops[0].type = o_cond;
            inst.ops[0].reg = y;
            inst.ops[1].type = o_near;
            inst.ops[1].addr = inst.get_next_word();
            return inst.size;

        case 5: // x3 z5
            if (!q) { // x3 z5 q0
                inst.itype = z80i_push;
                decode_pair(inst.ops[0], p);
                if (z80r_sp == inst.ops[0].reg) {
                    inst.ops[0].reg = z80r_af;
                }
            } else { // x3 z5 q1
                switch (p) {
                case 0: // x3 z5 q1 p0
                    inst.itype = z80i_call;
                    inst.ops[0].type = o_near;
                    inst.ops[0].addr = inst.get_next_word();
                    return inst.size;

                case 1: // x3 z5 q1 p1
                    // 0xDD prefix
                    break;

                case 2: // x3 z5 q1 p2
                    // 0xED prefix
                    break;

                case 3: // z3 z5 q1 p3
                    // 0xFD prefix
                    break;
                }
            }
            break;

        case 6: // x3 z6
            // table as consecutive enum values
            inst.itype = z80i_add + y;
            inst.ops[0].type = o_reg;
            inst.ops[0].reg = z80r_a;
            decode_nn(inst, inst.ops[1]);
            return inst.size;

        case 7: // x3 z7
            inst.itype = z80i_rst;
            inst.ops[0].type = o_near;
            inst.ops[0].addr = inst.get_next_byte() * 8;
            return inst.size;
        }
        break;
    }

    return 0;
}
