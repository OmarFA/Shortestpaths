#By Omar Azhar
CC=gcc
CFLAG=-o 
a.out: PA3.o 
	$(CC) $(CFLAG) run PA3.o
PA3.o: PA3.c
	$(CC) -c PA3.c
clean:
	rm -f a.out
	rm -f *.o
	rm -f *~
	rm -f core