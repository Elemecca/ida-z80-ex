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



static int inspect_op_read(const insn_t &inst, const op_t &op) {
    switch (op.type) {
    case o_reg:
    case o_phrase:
        // register operands don't create xrefs
        break;

    case o_cond:
        // conditions don't create xrefs
        break;

    case o_mem:
        {   ea_t ea = map_data_ea(inst, op);
            inst.add_dref(ea, op.offb, dr_R);
            inst.create_op_data(ea, op);
        }
        break;

    case o_imm:
        // should this create xrefs? other modules do
        break;

    case o_near:
        {   ea_t ea = map_code_ea(inst, op);
            int call = has_insn_feature(inst.itype, CF_CALL);
            int near = inst.cs == ((ea - op.addr) >> 4);
            inst.add_cref(ea, op.offb, (
                call ? (near ? fl_CN : fl_CF)
                     : (near ? fl_JN : fl_JF)
            ));

            return !call || func_does_return(ea);
        }
        break;
    }

    return 1;
}


static void inspect_op_write(const insn_t &inst, const op_t &op) {
    switch (op.type) {
    case o_reg:
    case o_phrase:
        // register operands don't create xrefs
        break;

    case o_cond:
        // conditions don't create xrefs
        break;

    case o_mem:
        {   ea_t ea = map_data_ea(inst, op);
            inst.add_dref(ea, op.offb, dr_W);
            inst.create_op_data(ea, op);
        }
        break;

    case o_imm:
        // should this create xrefs? other modules do
        break;

    case o_near:
        // jumps/calls never write to their target address
        break;
    }
}


int z80_emulate(const insn_t &inst) {
    uint32 features = inst.get_canon_feature();
    int flow = 1;

    if (features & CF_CHG1) {
        inspect_op_write(inst, inst.ops[0]);
    } else if (features & CF_USE1) {
        flow = flow && inspect_op_read(inst, inst.ops[0]);
    }

    if (features & CF_CHG2) {
        inspect_op_write(inst, inst.ops[1]);
    } else if (features & CF_USE2) {
        flow = flow && inspect_op_read(inst, inst.ops[1]);
    }


    switch (inst.itype) {
    case z80i_ret:
        flow = false;
        break;
    }

    if (flow) {
        inst.add_cref(inst.ea + inst.size, 0, fl_F);
    }

    return 1;
};
