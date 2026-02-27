CC = gcc
CFLAGS = -g
RM = rm -f

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
TARGET = server

default: all

all: $(TARGET)
		
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c	
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ_FILES) $(TARGET) 
