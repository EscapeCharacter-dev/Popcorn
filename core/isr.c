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
    MonitorPuts(", 0x");
    MonitorPutiX(regs->err_code);
    MonitorPutc('\n');
    MonitorPuts("Additionnal register info:\n");
    MonitorPuts("\tDS  = 0x"); MonitorPutiX(regs->ds);  MonitorPutc('\n');
    MonitorPuts("\tEDI = 0x"); MonitorPutiX(regs->edi); MonitorPutc('\n');
    MonitorPuts("\tESI = 0x"); MonitorPutiX(regs->esi); MonitorPutc('\n');
    MonitorPuts("\tEBP = 0x"); MonitorPutiX(regs->ebp); MonitorPutc('\n');
    MonitorPuts("\tESP = 0x"); MonitorPutiX(regs->esp); MonitorPutc('\n');
    MonitorPuts("\tEBX = 0x"); MonitorPutiX(regs->ebx); MonitorPutc('\n');
    MonitorPuts("\tEDX = 0x"); MonitorPutiX(regs->edx); MonitorPutc('\n');
    MonitorPuts("\tECX = 0x"); MonitorPutiX(regs->ecx); MonitorPutc('\n');
    MonitorPuts("\tEAX = 0x"); MonitorPutiX(regs->eax); MonitorPutc('\n');
    MonitorPuts("\tEIP = 0x"); MonitorPutiX(regs->eip); MonitorPutc('\n');
    MonitorPuts("\tCS  = 0x"); MonitorPutiX(regs->cs);  MonitorPutc('\n');
    MonitorPuts("\tSS  = 0x"); MonitorPutiX(regs->ss);  MonitorPutc('\n');
    MonitorPuts("\tUESP = 0x"); MonitorPutiX(regs->useresp); MonitorPutc('\n');
    MonitorPuts("\tEFLAGS = 0x"); MonitorPutiX(regs->eflags); MonitorPutc('\n');

    if (interruptHandlers[regs->int_no] >= 40)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);

    if (interruptHandlers[regs->int_no] != 0)
    {
        interruptHandlers[regs->int_no](*regs);
    }

    if (regs->int_no < 32) while (1) {}
}

void IRQHandler(Registers_t *regs)
{
    if (interruptHandlers[regs->int_no] != 0)
    {
        interruptHandlers[regs->int_no](*regs);
    }
    
    /* EOI part */

    if (interruptHandlers[regs->int_no] >= 40)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}