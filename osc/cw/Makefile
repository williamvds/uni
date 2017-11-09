CC = gcc
CFLAGS = -std=c11
CPPFLAGS = -Wall -g -O2 -static
LDFLAGS = -lpthread
PROGS = task1a task1b task2 task3 task4 task5

all: $(PROGS)

task1a task2b: LDFLAGS=

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ coursework.c $<

clean:
	@rm -f *.out $(PROGS)
