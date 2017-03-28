CC = gcc
DEBUG = -g
CFLAGS = -std=c99 -Wall -Wextra

test_BitArray : BitArray.o
	$(CC) $(CFLAGS) BitArray.o test_BitArray.c -o test_BitArray

BitArray.o :
	$(CC) $(CFLAGS) BitArray.c -c

clean:
	rm *.o test_BitArray
