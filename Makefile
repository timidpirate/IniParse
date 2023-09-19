.phony: install tests clean
		 
iniparse:	./src/trim.c ./src/iniparse.c
		gcc -o $@ $^

./src/trim.c:	../Common/Trim/src/trim.c ../Common/Trim/src/trim.h
		cp ../Common/Trim/src/trim.h ./src/trim.h
		cp ../Common/Trim/src/trim.c ./src/trim.c

install: iniparse
		cp ./iniparse ~/bin/iniparse

test: iniparse
		cd tests && ./run
		
clean:
		rm -rf ./iniparse
		rm -rf ./tests/op*
