CC=gcc
CFLAGS=-I.

main: main.c
	$(CC) main.c -o server;
	$(CC) client.c -o client;

clean:
	rm server client