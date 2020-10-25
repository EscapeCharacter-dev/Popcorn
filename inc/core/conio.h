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

#ifndef __CONIO_H__
#define __CONIO_H__

#include "common.h"

/* Color defs */

    #define     BLACK   0x000000
    #define     BLUE    0x0000AA
    #define     GREEN   0x00AA00
    #define     CYAN    0x00AAAA
    #define     RED     0xAA0000
    #define     PURPLE  0xAA00AA
    #define     BROWN   0xAA5500
    #define     GRAY    0xAAAAAA
    #define     DGRAY   0x555555
    #define     LBLUE   0x5555FF
    #define     LGREEN  0x55FF55
    #define     LCYAN   0x55FFFF
    #define     LRED    0xFF5555
    #define     LPURPLE 0xFF55FF
    #define     YELLOW  0xFFFF55
    #define     WHITE   0xFFFFFF

/* ********** */

void changeconv(volatile unsigned short *newconv);

void MonitorPuts(char *s);
void MonitorClear();
void MonitorPutc(char c);
void EnableCursor();
void MonitorPuti(int i);
void MonitorPutiX(int i);

#endif