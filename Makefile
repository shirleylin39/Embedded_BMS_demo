CC = gcc
CFLAGS = -Wall -pthread
INCLUDE = -Iinclude
SRC = src/main.c src/battery.c src/balance.c src/alert.c src/led.c src/logger.c
OUT = embedded_demo

all:
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) -o $(OUT)

clean:
	rm -f $(OUT)
