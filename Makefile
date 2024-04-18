rental: *.c *.h
	gcc -o rental *.c

run: rental
	./rental

.PHONY: run
