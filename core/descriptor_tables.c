#include "../inc/core/descriptor_tables.h"
#include "../mm/tinyalloc.h"
#include "../inc/core/asm.h"
#include "../inc/core/isr.h"

/* GDT STUFF BELOW */

extern void GdtFlush(uint32);
static void InitGdt();
static void GdtSetGate(int32, uint32, uint32, uint8, uint8);

#define GdtSetGate0() GdtSetGate(0, 0, 0, 0, 0)

GdtEntry gdtEntries[5];
GdtPtr   gdtPtr;

/* ****** IDT STUFF BELOW */

extern void IdtFlush(uint32);

static void InitIdt();
static void IdtSetGate(uint8, uint32, uint16, uint8);

IdtEntry idtEntries[256];
IdtPtr   idtPtr;

/* ***** MISC CODE BELOW */

extern ISR interruptHandlers[];

void InitDescriptorTables()
{
    InitGdt();
    InitIdt();
    memset(&interruptHandlers, 0, sizeof(ISR) * 256);
}

/* ***** GDT CODE BELOW */

static void InitGdt()
{
    gdtPtr.limit = (sizeof(GdtEntry) * 5) - 1;
    gdtPtr.base  = (uint32)&gdtEntries;

    GdtSetGate0();
    GdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    GdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    GdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    GdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    GdtFlush((uint32)&gdtPtr);
}

static void GdtSetGate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
    gdtEntries[num].base_low    =  (base & 0xFFFF);
    gdtEntries[num].base_middle =  (base >> 16) & 0xFF;
    gdtEntries[num].base_high   =  (base >> 24) & 0xFF;
    gdtEntries[num].limit_low   =  (limit & 0xFFFF);
    gdtEntries[num].granularity =  (limit >> 16) & 0xF;
    gdtEntries[num].granularity |= gran & 0xF0;
    gdtEntries[num].access      =  access;
}

/* ****** IDT CODE BELOW */

static void InitIdt()
{
    idtPtr.limit = sizeof(IdtEntry) * 256 - 1;
    idtPtr.base  = (uint32)&idtEntries;

    memset(&idtEntries, 0, sizeof(IdtEntry) * 256);

    /* IRQ remap */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    IdtSetGate(0, (uint32)ISR0, 0x8, 0x8E);
    IdtSetGate(1, (uint32)ISR1, 0x8, 0x8E);
    IdtSetGate(2, (uint32)ISR2, 0x8, 0x8E);
    IdtSetGate(3, (uint32)ISR3, 0x8, 0x8E);
    IdtSetGate(4, (uint32)ISR4, 0x8, 0x8E);
    IdtSetGate(5, (uint32)ISR5, 0x8, 0x8E);
    IdtSetGate(6, (uint32)ISR6, 0x8, 0x8E);
    IdtSetGate(7, (uint32)ISR7, 0x8, 0x8E);
    IdtSetGate(8, (uint32)ISR8, 0x8, 0x8E);
    IdtSetGate(9, (uint32)ISR9, 0x8, 0x8E);
    IdtSetGate(10, (uint32)ISR10, 0x8, 0x8E);
    IdtSetGate(11, (uint32)ISR11, 0x8, 0x8E);
    IdtSetGate(12, (uint32)ISR12, 0x8, 0x8E);
    IdtSetGate(13, (uint32)ISR13, 0x8, 0x8E);
    IdtSetGate(14, (uint32)ISR14, 0x8, 0x8E);
    IdtSetGate(15, (uint32)ISR15, 0x8, 0x8E);
    IdtSetGate(16, (uint32)ISR16, 0x8, 0x8E);
    IdtSetGate(17, (uint32)ISR17, 0x8, 0x8E);
    IdtSetGate(18, (uint32)ISR18, 0x8, 0x8E);
    IdtSetGate(19, (uint32)ISR19, 0x8, 0x8E);
    IdtSetGate(20, (uint32)ISR20, 0x8, 0x8E);
    IdtSetGate(21, (uint32)ISR21, 0x8, 0x8E);
    IdtSetGate(22, (uint32)ISR22, 0x8, 0x8E);
    IdtSetGate(23, (uint32)ISR23, 0x8, 0x8E);
    IdtSetGate(24, (uint32)ISR24, 0x8, 0x8E);
    IdtSetGate(25, (uint32)ISR25, 0x8, 0x8E);
    IdtSetGate(26, (uint32)ISR26, 0x8, 0x8E);
    IdtSetGate(27, (uint32)ISR27, 0x8, 0x8E);
    IdtSetGate(28, (uint32)ISR28, 0x8, 0x8E);
    IdtSetGate(29, (uint32)ISR29, 0x8, 0x8E);
    IdtSetGate(30, (uint32)ISR30, 0x8, 0x8E);
    IdtSetGate(31, (uint32)ISR31, 0x8, 0x8E);
    IdtSetGate(32, (uint32)IRQ0, 0x8, 0x8E);
    IdtSetGate(33, (uint32)IRQ1, 0x8, 0x8E);
    IdtSetGate(34, (uint32)IRQ2, 0x8, 0x8E);
    IdtSetGate(35, (uint32)IRQ3, 0x8, 0x8E);
    IdtSetGate(36, (uint32)IRQ4, 0x8, 0x8E);
    IdtSetGate(37, (uint32)IRQ5, 0x8, 0x8E);
    IdtSetGate(38, (uint32)IRQ6, 0x8, 0x8E);
    IdtSetGate(39, (uint32)IRQ7, 0x8, 0x8E);
    IdtSetGate(40, (uint32)IRQ8, 0x8, 0x8E);
    IdtSetGate(41, (uint32)IRQ9, 0x8, 0x8E);
    IdtSetGate(42, (uint32)IRQ10, 0x8, 0x8E);
    IdtSetGate(43, (uint32)IRQ11, 0x8, 0x8E);
    IdtSetGate(44, (uint32)IRQ12, 0x8, 0x8E);
    IdtSetGate(45, (uint32)IRQ13, 0x8, 0x8E);
    IdtSetGate(46, (uint32)IRQ14, 0x8, 0x8E);
    IdtSetGate(47, (uint32)IRQ15, 0x8, 0x8E);

    IdtFlush((uint32)&idtPtr);

}

static void IdtSetGate(uint8 num, uint32 base, uint16 sel, uint8 flags)
{
    idtEntries[num].base_lo = base & 0xFFFF;
    idtEntries[num].base_hi = (base >> 16) & 0xFFFF;
    idtEntries[num].sel     = sel;
    idtEntries[num].always0 = 0;
    idtEntries[num].flags   = flags;
}
