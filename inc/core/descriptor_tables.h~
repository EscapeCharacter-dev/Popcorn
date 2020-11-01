#ifndef __DESCRIPTOR_TABLES_H
#define __DESCRIPTOR_TABLES_H

#include "common.h"

typedef struct GdtEntryStruct_t
{

    uint16 limit_low;
    uint16 base_low;
    uint8  base_middle;
    uint8  access;
    uint8  granularity;
    uint8  base_high;

} packed GdtEntry;

typedef struct GdtPtrStruct_t
{

    uint16 limit;
    uint32 base;

} packed GdtPtr;

typedef struct IdtEntryStruct_t
{

    uint16 base_lo;
    uint16 sel;
    uint8  always0;
    uint8  flags;
    uint16 base_hi;

} packed IdtEntry;

typedef struct IdtPointerStruct_t
{

    uint16 limit;
    uint32 base;

} packed IdtPtr;

void InitDescriptorTables();

/* ISRs */

#define __exv extern void

__exv ISR0();
__exv ISR1();
__exv ISR2();
__exv ISR3();
__exv ISR4();
__exv ISR5();
__exv ISR6();
__exv ISR7();
__exv ISR8();
__exv ISR9();
__exv ISR10();
__exv ISR11();
__exv ISR12();
__exv ISR13();
__exv ISR14();
__exv ISR15();
__exv ISR16();
__exv ISR17();
__exv ISR18();
__exv ISR19();
__exv ISR20();
__exv ISR21();
__exv ISR22();
__exv ISR23();
__exv ISR24();
__exv ISR25();
__exv ISR26();
__exv ISR27();
__exv ISR28();
__exv ISR29();
__exv ISR30();
__exv ISR31();
__exv IRQ0();
__exv IRQ1();
__exv IRQ2();
__exv IRQ3();
__exv IRQ4();
__exv IRQ5();
__exv IRQ6();
__exv IRQ7();
__exv IRQ8();
__exv IRQ9();
__exv IRQ10();
__exv IRQ11();
__exv IRQ12();
__exv IRQ13();
__exv IRQ14();
__exv IRQ15();

#endif