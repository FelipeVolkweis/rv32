CC = gcc
APP_NAME = exec
CFLAGS = -Wall 
INCLUDES = -I ./include
SRC = src/*.c
MAIN = ./main.c

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(MAIN) $(SRC) -o $(APP_NAME)

clean:
	rm -f $(APP_NAME)