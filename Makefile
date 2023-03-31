
run: tema1
	./tema1

build: tema1.c datatypes.c
	gcc -g tema1.c datatypes.c -Wall -o tema1

zip: tema1.c datatypes.c datatypes.h README Makefile
	zip -r tema1.zip tema1.c datatypes.c datatypes.h README Makefile

.PHONY: clean

clean:
	rm tema1