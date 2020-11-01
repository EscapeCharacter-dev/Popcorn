#ifndef __ISR_H
#define __ISR_H

#include "common.h"

typedef struct Registers_t_
{

    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 

} packed Registers_t;

typedef void (*ISR)(Registers_t);
void RegisterInterruptHandler(uint8 n, ISR handler);

#endif