/****************************************************************************
 * arch/xtensa/include/iss-hifi4/tie.h
 * compile-time HAL definitions dependent on CORE & TIE configuration
 *
 *  NOTE:  This header file is not meant to be included directly.
 *
 * This header file describes this specific Xtensa processor's TIE extensions
 * that extend basic Xtensa core functionality.  It is customized to this
 * Xtensa processor configuration.
 *
 * Customer ID=16861; Build=0x92d7c;
 * Copyright (c) 1999-2021 Cadence Design Systems Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/

#ifndef XTENSA_CORE_TIE_H
#define XTENSA_CORE_TIE_H

/* parasoft-begin-suppress ALL "This file not MISRA checked." */

#define XCHAL_CP_NUM            1       /* number of coprocessors */
#define XCHAL_CP_MAX            2       /* max CP ID + 1 (0 if none) */
#define XCHAL_CP_MASK           0x02    /* bitmask of all CPs by ID */
#define XCHAL_CP_PORT_MASK      0x00    /* bitmask of only port CPs */

/*  Basic parameters of each coprocessor:  */
#define XCHAL_CP1_NAME                  "AudioEngineLX"
#define XCHAL_CP1_IDENT                 AudioEngineLX
#define XCHAL_CP1_SA_SIZE               208 /* size of state save area */
#define XCHAL_CP1_SA_ALIGN              8   /* min alignment of save area */
#define XCHAL_CP_ID_AUDIOENGINELX       1   /* coprocessor ID (0..7) */

/*  Filler info for unassigned coprocessors, to simplify arrays etc:  */
#define XCHAL_CP0_SA_SIZE       0
#define XCHAL_CP0_SA_ALIGN      1
#define XCHAL_CP2_SA_SIZE       0
#define XCHAL_CP2_SA_ALIGN      1
#define XCHAL_CP3_SA_SIZE       0
#define XCHAL_CP3_SA_ALIGN      1
#define XCHAL_CP4_SA_SIZE       0
#define XCHAL_CP4_SA_ALIGN      1
#define XCHAL_CP5_SA_SIZE       0
#define XCHAL_CP5_SA_ALIGN      1
#define XCHAL_CP6_SA_SIZE       0
#define XCHAL_CP6_SA_ALIGN      1
#define XCHAL_CP7_SA_SIZE       0
#define XCHAL_CP7_SA_ALIGN      1

/*  Save area for non-coprocessor optional and custom (TIE) state:  */
#define XCHAL_NCP_SA_SIZE       28
#define XCHAL_NCP_SA_ALIGN      4

/*  Total save area for optional and custom state (NCP + CPn):  */
#define XCHAL_TOTAL_SA_SIZE     240 /* with 16-byte align padding */
#define XCHAL_TOTAL_SA_ALIGN    8   /* actual minimum alignment */

/* Detailed contents of save areas.
 * NOTE:  caller must define the XCHAL_SA_REG macro (not defined here)
 * before expanding the XCHAL_xxx_SA_LIST() macros.
 *
 * XCHAL_SA_REG(s,ccused,abikind,kind,opt,name,galign,align,asize,
 *              dbnum,base,regnum,bitsz,gapsz,reset,x...)
 *
 *  s = passed from XCHAL_*_LIST(s), eg. to select how to expand
 *  ccused = set if used by compiler without special options or code
 *  abikind = 0 (caller-saved), 1 (callee-saved), or 2 (thread-global)
 *  kind = 0 (special reg), 1 (TIE user reg), or 2 (TIE regfile reg)
 *  opt = 0 (custom TIE extension or coprocessor), or 1 (optional reg)
 *  name = lowercase reg name (no quotes)
 *  galign = group byte alignment (power of 2) (galign >= align)
 *  align = register byte alignment (power of 2)
 *  asize = allocated size in bytes (asize*8 == bitsz + gapsz + padsz)
 *    (not including any pad bytes required to galign this or next reg)
 *  dbnum = unique target number f/debug (see <xtensa-libdb-macros.h>)
 *  base = reg shortname w/o index (or sr=special, ur=TIE user reg)
 *  regnum = reg index in regfile, or special/TIE-user reg number
 *  bitsz = number of significant bits (regfile width, or ur/sr mask bits)
 *  gapsz = intervening bits, if bitsz bits not stored contiguously
 *  (padsz = pad bits at end [TIE regfile] or at msbits [ur,sr] of asize)
 *  reset = register reset value (or 0 if undefined at reset)
 *  x = reserved for future use (0 until then)
 *
 *  To filter out certain registers, e.g. to expand only the non-global
 *  registers used by the compiler, you can do something like this:
 *
 * #define XCHAL_SA_REG(s,ccused,p...) SELCC##ccused(p)
 * #define SELCC0(p...)
 * #define SELCC1(abikind,p...) SELAK##abikind(p)
 * #define SELAK0(p...)         REG(p)
 * #define SELAK1(p...)         REG(p)
 * #define SELAK2(p...)
 * #define REG(kind,tie,name,galn,aln,asz,csz,dbnum,base,rnum,bsz,rst,x...) \
 *      ...what you want to expand...
 */

#define XCHAL_NCP_SA_NUM        7
#define XCHAL_NCP_SA_LIST(s)    \
 XCHAL_SA_REG(s,1,0,0,1,          acclo, 4, 4, 4,0x0210,  sr,16 , 32,0,0,0) \
 XCHAL_SA_REG(s,1,0,0,1,          acchi, 4, 4, 4,0x0211,  sr,17 ,  8,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             br, 4, 4, 4,0x0204,  sr,4  , 16,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             m0, 4, 4, 4,0x0220,  sr,32 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             m1, 4, 4, 4,0x0221,  sr,33 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             m2, 4, 4, 4,0x0222,  sr,34 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             m3, 4, 4, 4,0x0223,  sr,35 , 32,0,0,0)

#define XCHAL_CP0_SA_NUM        0
#define XCHAL_CP0_SA_LIST(s)    /* empty */

#define XCHAL_CP1_SA_NUM        33
#define XCHAL_CP1_SA_LIST(s)    \
 XCHAL_SA_REG(s,0,0,1,0,        fcr_fsr, 8, 8, 8,0x1029,  ur,-1 ,  7,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,     ae_ovf_sar, 4, 4, 4,0x03F0,  ur,240, 15,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,     ae_bithead, 4, 4, 4,0x03F1,  ur,241, 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,ae_ts_fts_bu_bp, 4, 4, 4,0x03F2,  ur,242, 16,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,    ae_cw_sd_no, 4, 4, 4,0x03F3,  ur,243, 29,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,     ae_cbegin0, 4, 4, 4,0x03F6,  ur,246, 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,       ae_cend0, 4, 4, 4,0x03F7,  ur,247, 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,     ae_cbegin1, 4, 4, 4,0x03F8,  ur,248, 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,       ae_cend1, 4, 4, 4,0x03F9,  ur,249, 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed0, 8, 8, 8,0x1010, aed,0  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed1, 8, 8, 8,0x1011, aed,1  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed2, 8, 8, 8,0x1012, aed,2  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed3, 8, 8, 8,0x1013, aed,3  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed4, 8, 8, 8,0x1014, aed,4  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed5, 8, 8, 8,0x1015, aed,5  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed6, 8, 8, 8,0x1016, aed,6  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed7, 8, 8, 8,0x1017, aed,7  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed8, 8, 8, 8,0x1018, aed,8  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aed9, 8, 8, 8,0x1019, aed,9  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,          aed10, 8, 8, 8,0x101A, aed,10 , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,          aed11, 8, 8, 8,0x101B, aed,11 , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,          aed12, 8, 8, 8,0x101C, aed,12 , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,          aed13, 8, 8, 8,0x101D, aed,13 , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,          aed14, 8, 8, 8,0x101E, aed,14 , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,          aed15, 8, 8, 8,0x101F, aed,15 , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aep0, 1, 1, 1,0x1024, aep,0  ,  8,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aep1, 1, 1, 1,0x1025, aep,1  ,  8,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aep2, 1, 1, 1,0x1026, aep,2  ,  8,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,           aep3, 1, 1, 1,0x1027, aep,3  ,  8,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             u0, 8, 8, 8,0x1020,   u,0  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             u1, 8, 8, 8,0x1021,   u,1  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             u2, 8, 8, 8,0x1022,   u,2  , 64,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             u3, 8, 8, 8,0x1023,   u,3  , 64,0,0,0)

#define XCHAL_CP2_SA_NUM        0
#define XCHAL_CP2_SA_LIST(s)    /* empty */

#define XCHAL_CP3_SA_NUM        0
#define XCHAL_CP3_SA_LIST(s)    /* empty */

#define XCHAL_CP4_SA_NUM        0
#define XCHAL_CP4_SA_LIST(s)    /* empty */

#define XCHAL_CP5_SA_NUM        0
#define XCHAL_CP5_SA_LIST(s)    /* empty */

#define XCHAL_CP6_SA_NUM        0
#define XCHAL_CP6_SA_LIST(s)    /* empty */

#define XCHAL_CP7_SA_NUM        0
#define XCHAL_CP7_SA_LIST(s)    /* empty */

/* Byte length of instruction from its first byte, per FLIX.  */

#define XCHAL_BYTE0_FORMAT_LENGTHS    \
    3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11,\
    3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11,\
    3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11,\
    3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11,\
    3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11,\
    3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11,\
    3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11,\
    3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,6,11

/* parasoft-end-suppress ALL "This file not MISRA checked." */

#endif /* XTENSA_CORE_TIE_H */
