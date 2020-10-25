#include "../inc/core/timer.h"
#include "../inc/core/isr.h"
#include "../inc/core/conio.h"
#include "../inc/core/asm.h"

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

uint32 tick = 0;

static void TimerCallback(Registers_t regs)
{
    tick++;
    MonitorPuts("Tick: ");
    MonitorPuti(tick);
    MonitorPutc('\n');
}

void InitTimer(uint32 frequency)
{
    MonitorPuts("Starting initialization...\n");

    RegisterInterruptHandler(IRQ0, &TimerCallback);

    uint32 divisor = 1193180 / frequency;

    outb(0x43, 0x36);

    uint8 l = (uint8) (divisor & 0xFF);
    uint8 h = (uint8) ((divisor >> 8));

    outb(0x40, l);
    outb(0x40, h);
}