CC=gcc
CFLAGS=-Wall -fPIC

all: apache-rootkit.so

apache-rootkit.so: apache-rootkit.o
	$(CC) -shared -o $@ $^

apache-rootkit.o: apache-rootkit.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o *.so