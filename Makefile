rental: *.c *.h
	gcc -o rental *.c -g

run: rental
	./rental

docs:
	doxygen

.PHONY: run docs
