Memset:
    push edi

    mov ecx, [esp + 16]
    mov al, [esp + 12]
    mov edi, [esp + 8]
    rep stosb

    mov eax, [esp + 8]
    pop edi
    ret


