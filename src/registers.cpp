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

#include "registers.hpp"

// indexes must match register_id in <registers.hpp>
const char* const z80_register_names[] = {
    "a", "f",
    "b", "c",
    "d", "e",
    "h", "l",

    "af",
    "bc",
    "de",
    "hl",

    "ix",
    "iy",

    "pc",
    "sp",

    "i",
    "r",

    "cs",
    "ds"
};
