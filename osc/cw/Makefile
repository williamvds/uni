CC = gcc
CFLAGS = -std=c11
CPPFLAGS = -Wall -O2
LDFLAGS = -pthread
PROGS = task1a task1b task2 task3 task4 task5

all: $(PROGS)

task1a task1b: LDFLAGS=

%: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ coursework.c $<

clean:
	@rm -f *.out $(PROGS)
