CC=gcc
CFLAGS=-std=c11
CPPFLAGS=-Wall -g -O2 -static

%: %.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ coursework.c $<

clean:
	@rm -f *.out task1a task1b task2 task3 task4 task5
