#define the c compiler to user
CC=gcc

#define any compile-time flag
CFLAGS=-Wall -g

TARGET=pm

all: $(TARGET)

$(TARGET): $(TARGET).C
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
