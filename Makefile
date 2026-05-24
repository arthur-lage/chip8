CC = gcc
LDFLAGS = -LC:/SDL3/lib -lSDL3
TARGET = emulator
SRC = $(wildcard src/*.c)
CFLAGS = -Wall -Wextra -IC:/SDL3/include -Isrc

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

clean:
	del $(TARGET).exe