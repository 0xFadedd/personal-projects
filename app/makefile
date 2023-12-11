CC = clang
CFLAGS = -Wall -Wextra -g
TARGET = revenueModel

all: $(TARGET)

$(TARGET): revenueModel.c
	$(CC) $(CFLAGS) -o $(TARGET) revenueModel.c

clean:
	rm -f $(TARGET)