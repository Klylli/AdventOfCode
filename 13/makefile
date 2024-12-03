CFLAGS := -std=c99 -pedantic -Wall -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_POSIX_C_SOURCE=200809L -g
HEADERS := $(wildcard *.h)
OBJECTS := $(patsubst %.c, %.o, $(wildcard *.c))
reflection2: $(OBJECTS)
	gcc -o reflection2 reflection2.o
%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $<
all: reflection2
clean: 
	rm -f reflection2 *.o
