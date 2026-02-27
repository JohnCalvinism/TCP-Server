CC = gcc
CFLAGS = -g
RM = rm -f

default: all

all: TCP-Server
		
TCP-Server: TCP-Server.c	
	$(CC) $(CFLAGS) -o TCP-Server TCP-Server.c

clean: 
	$(RM) 
