rental: *.c *.h
	gcc -o rental *.c -g

run: rental
	./rental

.PHONY: run
