CC = gcc
CFLAGS = -I./../../include -Wall -std=c11 -pedantic -g
LDFLAGS = '-Wl,-rpath,$$ORIGIN/../lib' -L./../../lib -lUtils
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

all: rpg

%.d: %.c
	$(CC) $(CFLAGS) -MM $^ > $@
-include $(SRC:.c=.d)

rpg: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	rm -f *.o *.d rpg