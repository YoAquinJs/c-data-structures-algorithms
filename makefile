CC = gcc
CFLAGS = -Wall -Wextra

DSA = dsa-ctest
TARGET ?= $(DSA)

# directories

SRC_DIR = .
UTILS_DIR = utils
BUILD_DIR = build

STANDALONES_DIR = standalones

# DSA-ctest suite category dirs

SEARCHING_DIR = searching
SORTING_DIR = sorting

# files and obj files

UTILS_FILES = $(wildcard $(UTILS_DIR)/*.c)
UTILS_OBJS = $(UTILS_FILES:.c=.o)

DSA_FILES = $(wildcard $(SRC_DIR)/*.c) \
			$(wildcard $(SEARCHING_DIR)/*.c) \
			$(wildcard $(SORTING_DIR)/*.c)
DSA_OBJS = $(DSA_FILES:.c=.o)

STANDALONE_FILES = $(wildcard $(STANDALONES_DIR)/*)
STANDALONE_TARGETS := $(notdir $(STANDALONE_FILES:.c=))

# execution rules

all: $(TARGET)

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET) || true

# dsa test suite rules

$(DSA): $(DSA_OBJS) $(UTILS_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DSA_OBJS) $(UTILS_OBJS) -o $(BUILD_DIR)/$@

# book problems rules

$(STANDALONES_DIR): $(STANDALONE_TARGETS)

.PHONY: all $(STANDALONES_DIR)

%: $(STANDALONES_DIR)/%.c $(UTILS_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< $(UTILS_OBJS) -o $(BUILD_DIR)/$@

# general rules

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(DSA_OBJS) $(UTILS_OBJS)

clean-all:
	@rm -f $(DSA_OBJS) $(UTILS_OBJS)
	@rm -rf $(BUILD_DIR)

.PHONY: all clean

.PHONY: all clean-all
