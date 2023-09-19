.phony: install tests clean
		 
iniparse:	../Common/Trim/src/trim.c ./src/iniparse.c
		gcc -o $@ $^

install:
		cp ./iniparse ~/bin/iniparse

test: iniparse
		cd tests && ./run
		
clean:
		rm -rf ./iniparse
		rm -rf ./tests/op*
