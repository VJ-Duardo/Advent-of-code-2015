CC = gcc
CFLAGS = -I./../../include -Wall -std=c11 -pedantic -g
LDFLAGS = -lssl -lcrypto
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

all: mining

%.d: %.c
	$(CC) $(CFLAGS) -MM $^ > $@
-include $(SRC:.c=.d)

mining: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	rm -f *.o *.d mining
