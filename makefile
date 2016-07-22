CC     = gcc
CFLAGS = -O3 -g -Wall -Wextra
FILE1 = i_quick_sort.c

qs :
	$(CC) $(CFLAGS) -o qs $(FILE1)

clean :
	-rm -f *.o *.core qs qs