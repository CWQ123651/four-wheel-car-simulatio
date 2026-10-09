CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude

SRC = main.c \
      src/car_state.c \
      src/car_control.c \
      src/car_wheel.c \
      src/car_status.c \
      src/cmd_parser.c

TARGET = car

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o src/*.o
