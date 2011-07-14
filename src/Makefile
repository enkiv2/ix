all: clean src

clean:
	rm -f *.o ixmage.elf doc.txt

src: clean
	nasm -felf start.asm -o 00entry.o
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o gdt.o -I ../include/ gdt.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o isrs.o -I ../include/ isrs.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o util.o -I ../include/ util.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o irq.o -I ../include/ irq.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o timer.o -I ../include/ timer.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o idt.o -I../include/ idt.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o kernel_assert.o -I../include/ kernel_assert.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o kernel_halt.o -I../include/ kernel_halt.s
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o io.o -I../include/ io.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o ix_main.o -I../include/ ix_main.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o kb.o -I../include/ kb.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o vga.o -I../include/ vga.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o zz.o -I../include/ zz.c
	gcc -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o kaukatcr.o -I../include/ kaukatcr.c
	ld -nostdlib -Tlink.ld *.o -o ixmage.elf

image: clean src
	mkdir -p mnt
	sudo mount -o loop fd.img ./mnt/
	sudo cp menu.lst ./mnt/boot/menu.cfg
	sudo cp ixmage.elf ./mnt/
	sudo umount ./mnt/

test: image
	qemu -no-reboot -no-shutdown -fda fd.img

install: src
	sudo cp ixmage.elf /boot/



