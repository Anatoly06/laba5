CC = gcc
CFLAGS = -Wall
TARGET = univer

all: $(TARGET)

$(TARGET): main.o univer.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o univer.o

main.o: main.c univer.h
	$(CC) $(CFLAGS) -c main.c

univer.o: univer.c univer.h
	$(CC) $(CFLAGS) -c univer.c

clean:
	rm -f *.o $(TARGET) students.bin

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
