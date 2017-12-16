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

#include <ida.hpp>
#include <idp.hpp>

#include "module.hpp"
#include "assemblers.hpp"
#include "registers.hpp"
#include "instructions.hpp"


static ssize_t idaapi notify(void *, int event, va_list args) {
    switch (event) {
    case processor_t::ev_ana_insn:
        return z80_analyze(*va_arg(args, insn_t*));

    default:
        return 0;
    }
}


static const char* const psnames[] = {
    "z80-ex",
    NULL
};

static const char* const plnames[] = {
    "Zilog Z80 (Improved)",
    NULL
};

processor_t LPH = {
    IDP_INTERFACE_VERSION,          // version
    0x8000 + PLFM_Z80,              // id
    0                               // flag
        | PRN_HEX
        | PR_SEGTRANS,
    0,                              // flag2

    8,                              // cnbits
    8,                              // dnbits

    psnames,                        // psnames
    plnames,                        // plnames

    z80_assemblers,                 // assemblers

    notify,                         // _notify

    z80_register_names,             // reg_names
    z80r_vds + 1,                   // regs_num

    z80r_vcs,                       // reg_first_sreg
    z80r_vds,                       // reg_last_sreg
    2,                              // segreg_size
    z80r_vcs,                       // reg_code_sreg
    z80r_vds,                       // reg_data_sreg

    // there are no known code prologues
    NULL,                           // codestart

    // we use the `is_ret_insn` event exclusively
    NULL,                           // retcodes

    z80i_null,                      // instruc_start
    z80i_last,                      // instruc_end
    z80_instructions,               // instruc

    // there is no hardware floating-point support
    0,                              // tbyte_size
    {0, 0, 0, 0},                   // real_width

    z80i_ret,                       // icode_return
};
