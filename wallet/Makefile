CC = gcc
OBJ = main.o functions.o
TARGET = wallet

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

main.o: main.c functions.h
	$(CC) -c main.c

functions.o: functions.c functions.h
	$(CC) -c functions.c

clean:
	$(RM) $(OBJ) $(TARGET)