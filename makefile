CC := gcc
CFLAGS := -Wall -Wextra
CR_LDFLAG = -lcriterion

DSA_TEST_SUITE := dsa-ctest

TARGET ?= $(DSA_TEST_SUITE)
ARGS ?=

RELEASE ?= 0
ABS_INCLUDE ?= 1

# debug flags
ifeq ($(RELEASE), 1)
	CFLAGS += -O2
else
	CFLAGS += -g -DDEBUG
endif

# directories

SRC_DIR := src
TESTS_DIR := tests
BUILD_DIR := build

ifeq ($(ABS_INCLUDE), 1)
	CFLAGS += -I './$(SRC_DIR)'
endif

DSA_DIR := dsa
UTILS_DIR := utils

# files and obj files

FILES = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(FILES:.c=.o)

TESTS_FILES = $(shell find $(TESTS_DIR) -name '*.c')
TESTS_OBJS = $(TESTS_FILES:.c=.o)

# execution rules

all: $(TARGET)

run: $(TARGET)
	@echo "./$(BUILD_DIR)/$(TARGET) $(ARGS)"
	@./$(BUILD_DIR)/$(TARGET) $(ARGS) || echo "exit with status code $$?"

.PHONY: all run

# dsa test suite rules

$(DSA_TEST_SUITE): $(BUILD_DIR)/$(DSA_TEST_SUITE)
.PHONY: $(DSA_TEST_SUITE)

$(BUILD_DIR)/$(DSA_TEST_SUITE): $(OBJS) $(TESTS_OBJS) | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(CR_LDFLAG) $(OBJS) $(TESTS_OBJS) -o $@

# general rules

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) $(CFLAGS) $(CR_LDFLAG) -c $< -o $@

clean:
	@rm -f $(OBJS)

clean-all: clean
	@rm -r $(BUILD_DIR)

.PHONY: clean clean-all
