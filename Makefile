all:
	gcc main.c reservation_functions.c -o reservation -lgdbm

clean:
	rm -f reservation