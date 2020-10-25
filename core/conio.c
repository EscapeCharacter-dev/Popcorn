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

#include "../inc/core/conio.h"
#include "../mm/tinyalloc.h"
#include "../inc/core/asm.h"

/* The video memory for the console (default) */
volatile unsigned short *convs = (volatile unsigned short*) 0xB8000;

/*
    Used for printing integers.
*/
char * itoa( int value, char * str, int base )
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

/*
    Change console video memory pointer.
*/
void changeconv(volatile unsigned short *newconv)
{
    if (newconv)
        convs = newconv;
}

uint8 cursor_y = 0, cursor_x = 0;

void EnableCursor()
{
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 1);
}

static void MoveCursor()
{
    uint16 cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3d4, 14);
    outb(0x3d5, cursorLocation >> 8);
    outb(0x3d4, 15);
    outb(0x3d5, cursorLocation);
}

static void Scroll()
{
    uint8 attribute = (0 << 4) | (15 & 0x0F);
    uint16 blank = 0x20 | (attribute << 8);
    if (cursor_y >= 25)
    {
        int i;
        for (i = 0*80; i < 24 * 80; i++)
        {
            convs[i] = convs[i + 80];
        }
        for (i = 24 * 80; i < 25 * 80; i++)
        {
            convs[i] = blank;
        }
        cursor_y = 24;
    }
}

void MonitorPutc(char c)
{
    uint8 backcolor = 0;
    uint8 forecolor = 15;
    uint8 attributebyte = (backcolor << 4) | (forecolor & 0x0F);
    uint16 attribute = attributebyte << 8;
    uint16 *location;

    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }
    else if (c == 0x09)
    {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    }
    else if (c == '\r')
    {
        cursor_x = 0;
    }
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if (c >= ' ')
    {
        location = convs + (cursor_y * 80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }

    Scroll();
    /*MoveCursor();*/
}

void MonitorClear()
{
    uint8 attribute = (0 << 4) | (15 & 0x0F);
    uint16 blank = 0x20 | (attribute << 8);

    for (int i = 0; i < 80 * 25; i++)
        convs[i] = blank;
    
    cursor_x = 0;
    cursor_y = 0;
    MoveCursor();
}

void MonitorPuts(char *s)
{
    int i = 0;
    while (s[i])
        MonitorPutc(s[i++]);
}

void MonitorPuti(int i)
{
    char str[10];
    itoa(i, str, 10);
    MonitorPuts(str);
}

void MonitorPutiX(int i)
{
    char str[8];
    itoa(i, str, 16);
    MonitorPuts(str);
}