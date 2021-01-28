CC = gcc
CFLAGS = -I./../../include -Wall -std=c11 -pedantic -g
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

all: houses

%.d: %.c
	$(CC) $(CFLAGS) -MM $^ > $@
-include $(SRC:.c=.d)

houses: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	rm -f *.o *.d houses