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

/* Compiler Includes */


/* Directory Includes */
#include "../inc/core/common.h"
#include "../inc/core/conio.h"
#include "../inc/core/descriptor_tables.h"
#include "../inc/core/timer.h"
#include "../inc/core/keyboard.h"

/* Kernel core entrypoint. This function will start all core subroutines.
   The loader will load the microkernel parts.
*/

void krnlep(void)
{
    InitDescriptorTables();
    InitTimer(50);
    InstallKeyboard();
}