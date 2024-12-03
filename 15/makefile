CFLAGS := -std=c99 -pedantic -Wall -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_POSIX_C_SOURCE=200809L -g
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c, %.o, $(wildcard *.c))
verification2: $(OBJECTS)
	gcc -o verification2 verification2.o
%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $<
all: verification2
clean: 
	rm -f verification2 *.o
