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

#include "instructions.hpp"

instruc_t z80_instructions[] = {
    {"", 0},

    // load
    {"ld",   CF_CHG1 | CF_USE2},
    {"ex",   CF_CHG1 | CF_CHG2},
    {"exx",  0},
    {"exaf", 0},
    {"push", CF_USE1},
    {"pop",  CF_CHG1},

    // jump
    {"jp",     CF_USE1 |                     CF_STOP},
    {"jpcc",   CF_USE1 | CF_USE2                    },
    {"jr",     CF_USE1 |                     CF_STOP},
    {"jrcc",   CF_USE1 | CF_USE2                    },
    {"djnz",   CF_USE1                              },
    {"call",   CF_USE1 |           CF_CALL          },
    {"callcc", CF_USE1 | CF_USE2 | CF_CALL          },
    {"ret",    CF_USE1 |                     CF_STOP},
    {"retcc",  CF_USE1 |                     CF_STOP},

    // arithmetic
    {"add", CF_CHG1 | CF_USE2},
    {"adc", CF_CHG1 | CF_USE2},
    {"sub", CF_CHG1 | CF_USE2},
    {"sbc", CF_CHG1 | CF_USE2},
    {"and", CF_CHG1 | CF_USE2},
    {"xor", CF_CHG1 | CF_USE2},
    {"or",  CF_CHG1 | CF_USE2},
    {"cp",  CF_USE1 | CF_USE2},
    {"inc", CF_CHG1},
    {"dec", CF_CHG1},

    // shifty things
    {"rlca", 0},
    {"rrca", 0},
    {"rla",  0},
    {"rra",  0},
    {"daa",  0},
    {"cpl",  0},
    {"scf",  0},
    {"ccf",  0},

    // IO
    {"out", CF_USE1 | CF_USE2},
    {"in",  CF_CHG1 | CF_USE2},

    // control
    {"nop",  0},
    {"halt", 0},
    {"rst",  CF_USE1},
    {"di",   0},
    {"ei",   0},
};
