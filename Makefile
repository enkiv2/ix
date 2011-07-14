all: src

test: src
	make -C src/ test

src: FORCE
	make -C src/
	@echo
	@echo "Now run make test, to run in an emulator"
	@echo "or run make install to copy the image to /boot"
	@echo

clean:
	make -C src/ clean

push: clean update
	git commit -a
	git push origin master

update:
	rm -f src/fd.img
	git pull origin master 

pull: update

install:
	make -C src/ install
	@echo
	@echo "Make sure to edit your grub configuration to include /boot/image.elf if you have not yet done so!"
	@echo

doc:
	sh src/doc.sh > src/doc.txt

FORCE:

