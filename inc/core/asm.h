#ifndef __CORE_ASM_H
#define __CORE_ASM_H

#include "common.h"

void outb(ushort port, byte value);
byte inb(ushort port);

#endif