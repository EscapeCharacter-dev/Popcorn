[GLOBAL GdtFlush]

[EXTERN gdtPtr]

GdtFlush:
    ;mov eax, [esp + 4]
    ;lgdt [eax]

    ;mov ax, 0x10
    ;mov ds, ax
    ;mov es, ax
    ;mov fs, ax
    ;mov gs, ax
    ;mov ss, ax
    ;jmp 0x8:.Flush
    lgdt [gdtPtr]        ; Load the GDT with our '_gdtPointer' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.Flush
.Flush:
    ret



[GLOBAL IdtFlush]
[EXTERN idtPtr]

IdtFlush:
    lidt[idtPtr]
    sti
    ret