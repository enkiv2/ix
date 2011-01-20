all: src

test: src
	make -C src/ test

src:
	make -C src/

clean:
	make -C src/ clean


