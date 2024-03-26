TARGET = todo

CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR = src
INSTALL_DIR = /usr/local/bin

SOURCES := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(SRC_DIR)/*.h)
OBJECTS := $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
	rm -f $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

install: $(TARGET)
	cp $< $(INSTALL_DIR)

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
