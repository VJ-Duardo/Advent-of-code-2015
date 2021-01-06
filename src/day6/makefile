CC = gcc
CFLAGS = -I./../../include -Wall -std=c11 -pedantic -g
SRC = $(wildcard *.c)
SRC += ./../utils/utils.c
OBJS = $(SRC:.c=.o)

all: lights

%.d: %.c
	$(CC) $(CFLAGS) -MM $^ > $@
-include $(SRC:.c=.d)

lights: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)


.PHONY: clean
clean:
	rm -f *.o *.d lights
