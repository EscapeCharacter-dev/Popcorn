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

#include "../inc/core/asm.h"

void outb(ushort port, byte value)
{
    asm volatile("outb %0, %1" : "=a"(value) : "d"(port));
}

byte inb(ushort port)
{
    byte ret = 0;
    asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}