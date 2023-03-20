

run: tema1
	./tema1

build: tema1.c
	gcc tema1.c -o tema1

.PHONY: clean

clean:
	rm tema1