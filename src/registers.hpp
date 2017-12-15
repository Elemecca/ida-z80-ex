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

#ifndef __REGISTERS_HPP
#define __REGISTERS_HPP

#include <ida.hpp>
#include <idp.hpp>

extern const char* const z80_register_names[];

enum z80_register_id ENUM_SIZE(uint16) {
    z80r_a, z80r_f,
    z80r_b, z80r_c,
    z80r_d, z80r_e,
    z80r_h, z80r_l,

    z80r_af,
    z80r_bc,
    z80r_de,
    z80r_hl,

    z80r_ix,
    z80r_iy,

    z80r_pc,
    z80r_sp,

    z80r_i,
    z80r_r,

    z80r_vcs, // virtual code segment register
    z80r_vds  // virtual data segment register
};


#endif
