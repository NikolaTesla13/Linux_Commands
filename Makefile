
CC = gcc

LS = _ls
CAT = _cat

all: debug

debug: src/ls.c src/cat.c
	$(CC) -o bin/$(LS) src/ls.c
	$(CC) -o bin/$(CAT) src/cat.c

clean:
	rm bin/$(LS)
	rm bin/$(CAT)