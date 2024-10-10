CC = gcc
CDEBUG = -g -DDEBUG
CREALSE = -O2
CFLAGS = -Wall -Wextra

DSA_TEST_SUITE = dsa-ctest

TARGET ?= $(DSA_TEST_SUITE)
RELEASE ?= 0
ARGS ?=

# debug flags
ifeq ($(RELEASE), 1)
	CFLAGS += $(CREALSE)
else
	CFLAGS += $(CDEBUG)
endif

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

STANDALONE_FILES = $(shell find $(SRC_DIR)/$(STANDALONES_DIR) -name '*.c')
STANDALONE_SOURCES = $(subst $(SRC_DIR)/$(STANDALONES_DIR)/, , $(STANDALONE_FILES))
STANDALONE_TARGETS = $(subst .c, , $(STANDALONE_SOURCES))

# execution rules

all: $(TARGET)

run: $(TARGET)
	@echo "./$(BUILD_DIR)/$(TARGET) $(ARGS) "
	@./$(BUILD_DIR)/$(TARGET) $(ARGS) || echo "exit with status code $?"

.PHONY: all run

# dsa test suite rules

$(DSA_TEST_SUITE): $(BUILD_DIR)/$(DSA_TEST_SUITE)
.PHONY: $(DSA_TEST_SUITE)

$(BUILD_DIR)/$(DSA_TEST_SUITE): $(DSA_OBJS) $(UTILS_OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DSA_OBJS) $(UTILS_OBJS) -o $@

# standalones rules

$(STANDALONES_DIR): $(STANDALONE_TARGETS)

$(foreach target,$(STANDALONE_TARGETS),\
	$(eval $(target): $(BUILD_DIR)/$(target)))

$(BUILD_DIR)/%: $(STANDALONES_DIR)/%.c $(UTILS_OBJS) | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(UTILS_OBJS) -o $@

# general rules

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(DSA_OBJS) $(UTILS_OBJS)

clean-all: clean
	@rm -rf $(BUILD_DIR)

.PHONY: clean clean-all
