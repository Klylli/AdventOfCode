CFLAGS := -std=c99 -pedantic -Wall -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_POSIX_C_SOURCE=200809L -g
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c, %.o, $(wildcard *.c))
steps2: $(OBJECTS)
	gcc -o steps2 steps2.o
%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $<
all: steps2
clean: 
	rm -f steps2 *.o
