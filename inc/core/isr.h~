#ifndef __ISR_H
#define __ISR_H

#include "common.h"

typedef struct Registers_t_
{

    uint32 ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 int_no, err_code;
    uint32 eip, cs, eflags, useresp, ss;

} Registers_t;

typedef void (*ISR)(Registers_t);
void RegisterInterruptHandler(uint8 n, ISR handler);

#endif