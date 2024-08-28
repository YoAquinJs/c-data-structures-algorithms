CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR = .

SRC_FILES = $(wildcard $(SRC_DIR)/*.c) \
            $(wildcard searching/*.c) \
            $(wildcard sorting/*.c) \
            $(wildcard utils/*.c)

OBJ_FILES = $(SRC_FILES:.c=.o)

OUTPUT = dsa-ctest

all: $(OUTPUT)

$(OUTPUT): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_FILES)

.PHONY: all clean
