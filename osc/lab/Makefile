KEEP = $(wildcard *.c) Makefile labs.pdf samples
CLEAN = $(filter-out ${KEEP}, $(wildcard *))
clean:
	for FILE in ${CLEAN}; do rm $$FILE; done
