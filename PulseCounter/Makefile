CC = gcc
CFLAGS = -Wall -Iinclude
SRC = $(shell find src -name '*.c')
TARGET = programa

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
