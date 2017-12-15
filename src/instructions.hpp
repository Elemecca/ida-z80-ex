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

#ifndef __INSTRUCTIONS_HPP
#define __INSTRUCTIONS_HPP

#include <ida.hpp>
#include <idp.hpp>

// custom operator type for conditions
#define o_cond  o_idpspec0

enum z80_condition_id ENUM_SIZE(uint8) {
    oc_nz = 0,
    oc_z,
    oc_nc,
    oc_c,
    oc_po,
    oc_pe,
    oc_p,
    oc_m
};


extern instruc_t z80_instructions[];

enum z80_instruction_id ENUM_SIZE(uint16) {
    z80i_null,

    // load
    z80i_ld,
    z80i_ex,
    z80i_exx,
    z80i_exaf,
    z80i_push,
    z80i_pop,

    // jump
    z80i_jp,
    z80i_jpcc,
    z80i_jr,
    z80i_jrcc,
    z80i_djnz,
    z80i_call,
    z80i_callcc,
    z80i_ret,
    z80i_retcc,

    // arithmetic
    z80i_add, // table alu 0
    z80i_adc, // table alu 1
    z80i_sub, // table alu 2
    z80i_sbc, // table alu 3
    z80i_and, // table alu 4
    z80i_xor, // table alu 5
    z80i_or,  // table alu 6
    z80i_cp,  // table alu 7
    z80i_inc,
    z80i_dec,

    // shifty things
    z80i_rlca, // table x0z7 0
    z80i_rrca, // table x0z7 1
    z80i_rla,  // table x0z7 2
    z80i_rra,  // table x0z7 3
    z80i_daa,  // table x0z7 4
    z80i_cpl,  // table x0z7 5
    z80i_scf,  // table x0z7 6
    z80i_ccf,  // table x0z7 7

    // IO
    z80i_out,
    z80i_in,

    // control
    z80i_nop,
    z80i_halt,
    z80i_rst,
    z80i_di,
    z80i_ei,

    z80i_last
};

#endif
