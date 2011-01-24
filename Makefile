all: src

test: src
	make -C src/ test

src:
	make -C src/

clean:
	make -C src/ clean

push: clean update
	git commit -a
	git push origin master

update:
	git pull origin master 

