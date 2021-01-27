CC = gcc
CFLAGS = -I./../../include -Wall -std=c11 -pedantic -fpic
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

all: libUtils.so

%.d: %.c
	$(CC) $(CFLAGS) -MM $^ > $@
-include $(SRC:.c=.d)

libUtils.so: $(OBJS)
	$(CC) -shared -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	rm -f *.o *.d libUtils.so