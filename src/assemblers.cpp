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

#include "assemblers.hpp"

static const asm_t asm_zilog = {
    0                               // flags
        | ASH_HEXF0  // hex: 34h
        | ASD_DECF0  // dec: 34
        | ASO_OCTF0  // oct: 123o
        | ASB_BINF0  // bin: 010101b
        | AS_COLON   // data names are labels and need a colon
        | AS_ASCIIC  // strings accept C-like escapes
        | AS_N2CHR   // no two-byte character literals
        | AS_ONEDUP, // at most one array definition per line
    0,                              // uflag
    "Zilog Macro Assembler",        // name
    0,                              // help
    NULL,                           // header
    "org",                          // origin
    "end",                          // end
    ";",                            // cmnt
    '\'',                           // ascsep
    '\'',                           // accsep
    "'\"",                          // esccodes
    ".ascii",                       // a_ascii
    "db",                           // a_byte
    "dw",                           // a_word
    "dl",                           // a_dword
    NULL,                           // a_qword
    NULL,                           // a_oword
    ".float",                       // a_float
    NULL,                           // a_double
    NULL,                           // a_tbyte
    NULL,                           // a_packreal
    "#h [ #d ], #v",                // a_dups
    "ds %s",                        // a_bss
    "equ",                          // a_equ
    NULL,                           // a_seg
    "$",                            // a_curip
    NULL,                           // out_func_header
    NULL,                           // out_func_footer
    "public",                       // a_public
    NULL,                           // a_weak
    "extern",                       // a_extrn
    NULL,                           // a_comdef
    NULL,                           // get_type_name
    "align",                        // a_align
    ' ',                            // lbrace
    ' ',                            // rbrace
    "%",                            // a_mod
    "&",                            // a_band
    "|",                            // a_bor
    "^",                            // a_xor
    "~",                            // a_bnot
    "<<",                           // a_shl
    ">>",                           // a_shr
    NULL,                           // a_sizeof_fmt
    0,                              // flag2
    NULL,                           // cmnt2
    NULL,                           // low8
    NULL,                           // high8
    NULL,                           // low16
    NULL,                           // high16
    NULL,                           // a_include_fmt
    NULL,                           // a_vstruc_fmt
    NULL,                           // a_rva
    NULL,                           // a_yword
};

const asm_t* const z80_assemblers[] = {
    &asm_zilog,
};
