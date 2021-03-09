FILENAME=challenge3.c
main: $(FILENAME)
	gcc -O2 -march=native -g -lm $(FILENAME)
