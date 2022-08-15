CC = gcc
CFLAGS = -Wall -Og -g
CLIBS = -lcsapp -lpthread
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(CLIBS)

.PHONY: clean
clean:
	find ./ -type f -executable -print0 | xargs -0 rm -f --
