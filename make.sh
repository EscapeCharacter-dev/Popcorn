cc -m32 -ffreestanding -c -o bin/core.o core/core.c         -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./inc
cc -m32 -ffreestanding -c -o bin/conio.o core/conio.c       -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./inc
cc -m32 -ffreestanding -c -o bin/asm.o core/asm.c           -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./inc
cc -m32 -ffreestanding -c -o bin/tinyalloc.o mm/tinyalloc.c -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./inc
cc -m32 -ffreestanding -c -o bin/descriptor_tables.o core/descriptor_tables.c -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./inc
cc -m32 -ffreestanding -c -o bin/isr.o core/isr.c           -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./inc
cc -m32 -ffreestanding -c -o bin/timer.o core/timer.c       -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./inc
cc -m32 -ffreestanding -c -o bin/keyboard.o core/keyboard.c -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./inc
nasm -f elf -o bin/boot.o grub-boot/boot.S
as --32 -o bin/lm.o core/longmode.S
nasm -f elf -o bin/gdtUtils.o core/gdtUtils.S
nasm -f elf -o bin/interrupt.o core/interrupt.S
ld -m elf_i386 -T link.ld -o bin/popcorn bin/core.o bin/conio.o bin/boot.o bin/asm.o bin/tinyalloc.o bin/lm.o \
    bin/descriptor_tables.o bin/gdtUtils.o bin/isr.o bin/interrupt.o bin/timer.o bin/keyboard.o
cp bin/popcorn bin/image/boot/popcorn
cp grub-boot/grub.cfg bin/image/boot/grub/grub.cfg
grub-mkrescue -o bin/SimplixOS.iso bin/image