all: clean src

clean:
	rm -f *.o image.elf doc.txt

src: clean
	nasm -felf start.asm -o 00entry.o
	#nasm -felf  gdt.asm -o gdt.o
	#nasm -felf irq.asm -o irq.o
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o gdt.o -I ../include/ gdt.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o isrs.o -I ../include/ isrs.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o util.o -I ../include/ util.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o irq.o -I ../include/ irq.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o timer.o -I ../include/ timer.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o idt.o -I../include/ idt.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o kernel_assert.o -I../include/ kernel_assert.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o kernel_halt.o -I../include/ kernel_halt.s
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o io.o -I../include/ io.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o ix_main.o -I../include/ ix_main.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o kb.o -I../include/ kb.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o vga.o -I../include/ vga.c
	gcc -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -c -o zz.o -I../include/ zz.c
	ld -nostdlib -Tlink.ld *.o -o image.elf

image: clean src
	mkdir -p mnt
	sudo mount -o loop fd.img ./mnt/
	sudo cp menu.lst ./mnt/boot/menu.cfg
	sudo cp image.elf ./mnt/
	sudo umount ./mnt/

test: image
	qemu -no-reboot -no-shutdown -fda fd.img

doc:
	grep '//@' *.c ../include/*.h | sed -e 's/\/\/\@/\n\t/g' | sed -e 's/\:/\t/g' > doc.txt
