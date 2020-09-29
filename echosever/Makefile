CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm

all: server client

server: echoServer.c
	${CC} echoServer.c -o server

client: echoClient.c
	${CC} echoClient.c -o client

clean:
	rm -f *.o *~