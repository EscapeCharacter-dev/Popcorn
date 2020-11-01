#include "../inc/core/isr.h"
#include "../inc/core/conio.h"
#include "../inc/core/asm.h"

ISR interruptHandlers[256];

void RegisterInterruptHandler(uint8 n, ISR handler)
{
    interruptHandlers[n] = handler;
}

void ISRHandler(Registers_t *regs)
{
    MonitorPuts("Received interrupt from CPU (or software): ");
    MonitorPuti(regs->int_no);
    MonitorPutc('\n');

    if (interruptHandlers[regs->int_no] != 0)
    {
        interruptHandlers[regs->int_no](*regs);
    }
}

void IRQHandler(Registers_t *regs)
{   


    /* EOI part */

    if (interruptHandlers[regs->int_no] >= 40)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);

    if (interruptHandlers[regs->int_no] != 0)
    {
        interruptHandlers[regs->int_no](*regs);
    }
}