CFLAGS =

all: main test

debug:  CFLAGS+= -g
debug: main test

main : main.c
	gcc $(CFLAGS) -o main main.c
test : test.c
	gcc $(CFLAGS) -o test test.c

clean:
	@rm -f main test
