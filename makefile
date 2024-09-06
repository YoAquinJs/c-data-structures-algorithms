CC = gcc
CFLAGS = -Wall -Wextra

DSA = dsa-ctest

# directories

SRC_DIR = .
UTILS_DIR = utils
BUILD_DIR = build

BOOK_PROBLEMS_DIR = book-problems

#DSA-ctest suite category dirs

SEARCHING_DIR = searching
SORTING_DIR = sorting

# files and obj files

UTILS_FILES = $(wildcard $(UTILS_DIR)/*.c)
UTILS_OBJS = $(UTILS_FILES:.c=.o)

DSA_FILES = $(wildcard $(SRC_DIR)/*.c) \
			$(wildcard $(SEARCHING_DIR)/*.c) \
			$(wildcard $(SORTING_DIR)/*.c)
DSA_OBJS = $(DSA_FILES:.c=.o)

# dsa test suite rules

all: $(DSA)

run: $(DSA)
	./$(BUILD_DIR)/$(DSA)

$(DSA): $(DSA_OBJS) $(UTILS_OBJS)
	$(CC) $(CFLAGS) $(DSA_OBJS) $(UTILS_OBJS) -o $(BUILD_DIR)/$@

# book problems rules

%: $(BOOK_PROBLEMS_DIR)/%.c $(UTILS_OBJS)
	$(CC) $(CFLAGS) $< $(UTILS_OBJS) -o $(BUILD_DIR)/$@

# general rules

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(DSA_OBJS) $(UTILS_OBJS)

.PHONY: all clean

