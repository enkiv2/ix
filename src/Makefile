img := img.iso
srcs := $(wildcard *.c *.s)
objs := $(srcs:%.c=%.o) 00entry.o
objs := $(objs:%.s=%.o)
target := image.elf
AS=$(CC)
CFLAGS = -Wall -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -I../include/
ASFLAGS := $(CFLAGS) -c

all: src

clean:
	-rm -f $(objs) $(target) $(img) doc.txt

00entry.o: start.asm
	nasm -felf $< -o $@

$(target): link.ld $(objs)
	ld -nostdlib -Tlink.ld $(objs) -o image.elf

src: $(target)

image: $(img)

$(img): $(target) menu.lst
	mkdir -p iso/boot/grub
	cp /boot/grub/stage2_eltorito iso/boot/grub
	sudo cp menu.lst iso/boot/grub/menu.lst
	sudo cp $(target) iso/
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot \
         -boot-load-size 4 -boot-info-table -o $(img) iso/

test: image
	qemu -no-reboot -no-shutdown -boot d -cdrom $(img)

install: src
	sudo cp $(target) /boot/

.PHONY: image test install all src clean

