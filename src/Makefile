img := img.iso
srcs := $(wildcard *.c *.s)
objs := 00entry.o $(srcs:%.c=%.o)
objs := $(objs:%.s=%.o)
target := ixmage.elf
AS=$(CC)
CFLAGS = -Wall -std=gnu99 -mtune=i386 -mno-mmx -mno-3dnow -mno-sse2 -mno-sse3 -mno-sse -mno-tls-direct-seg-refs -nostdlib -nostdinc -ffreestanding -I../include/
ASFLAGS := $(CFLAGS) -c

all: src

clean:
	-rm -f $(objs) $(target) $(img) doc.txt

00entry.o: start.asm
	nasm -f elf32 $< -o $@

$(target): link.ld $(objs)
	ld -nostdlib -Tlink.ld $(objs) -o $(target)

src: $(target)

image: $(img)

$(img): $(target) menu.lst
	mkdir -p iso/boot/grub
	cp /boot/grub/stage2_eltorito iso/boot/grub
	cp menu.lst iso/boot/grub/menu.lst
	cp $(target) iso/
	mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot \
         -boot-load-size 4 -boot-info-table -o $(img) iso/

test: image
	qemu -no-reboot -no-shutdown -boot d -cdrom $(img)

install: src
	@echo "Don't do this! Read the README for more information"

.PHONY: image test install all src clean

