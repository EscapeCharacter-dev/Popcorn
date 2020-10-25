/*  This file is part of Popcorn Kernel.

    Popcorn is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Popcorn is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Popcorn. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __COMMON_H__
#define __COMMON_H__

    /* typedefs */

    #if __x86_64__ || __ppc64__
    typedef unsigned long long  uword;           /* Unsigned word, size of the processor architecture. */
    typedef long long           word;            /* Word, size of the processor architecture. */
    #define WORD_SIZE           8
    #else

    typedef unsigned long       uword;           /* Unsigned word, size of the processor architecture. */
    typedef long                word;            /* Word, size of the processor architecture. */
    #define WORD_SIZE           4
    #endif

    typedef signed char         sbyte, schar, int8, I8;
    typedef unsigned char              byte, uint8, U8, HWORD, _hword;
    typedef short                           int16, I16;
    typedef unsigned short         ushort, uint16, U16, WORD, _word;
    typedef long                            int32, I32;
    typedef unsigned long            uint, uint32, U32, DWORD, _dword;
    typedef long long                llong, int64, I64;
    typedef unsigned long long     ullong, uint64, U64, QWORD, _qword;
    typedef void                          function, U0;
    typedef void*                                  ptr;
    typedef unsigned long long size_t;

    #define NULL 0
    #define bool int
    #define true 1
    #define false

    #define packed __attribute__((packed))
    #define interrupt __attribute__((interrupt))
    #define aligned(x) __attribute__((aligned(x)))

#endif