CC := gcc
CDEBUG := -g -DDEBUG
CRELEASE := -O2
CFLAGS := -Wall -Wextra

DSA_TEST_SUITE := dsa-ctest

TARGET ?= $(DSA_TEST_SUITE)
ARGS ?=

RELEASE ?= 0
ABS_INCLUDE ?= 1

# debug flags
ifeq ($(RELEASE), 1)
	CFLAGS += $(CRELEASE)
else
	CFLAGS += $(CDEBUG)
endif

# directories

SRC_DIR := src
ifeq ($(ABS_INCLUDE), 1)
	CFLAGS += -I './$(SRC_DIR)'
endif

UTILS_DIR := utils
BUILD_DIR := build

DSA_DIR := dsa
STANDALONES_DIR := standalones

# files and obj files

UTILS_FILES = $(shell find $(SRC_DIR)/$(UTILS_DIR) -name '*.c')
UTILS_OBJS = $(UTILS_FILES:.c=.o)

DSA_FILES = $(shell find $(SRC_DIR)/$(DSA_DIR) -name '*.c')
DSA_OBJS = $(DSA_FILES:.c=.o)

STANDALONE_FILES = $(shell find $(SRC_DIR)/$(STANDALONES_DIR) -name '*.c')
STANDALONE_SOURCES = $(subst $(SRC_DIR)/$(STANDALONES_DIR)/, , $(STANDALONE_FILES))
STANDALONE_TARGETS = $(subst .c, , $(STANDALONE_SOURCES))

# execution rules

all: $(TARGET)

run: $(TARGET)
	@echo "./$(BUILD_DIR)/$(TARGET) $(ARGS) "
	@./$(BUILD_DIR)/$(TARGET) $(ARGS) || echo "exit with status code $$?"

.PHONY: all run

# dsa test suite rules

$(DSA_TEST_SUITE): $(BUILD_DIR)/$(DSA_TEST_SUITE)
.PHONY: $(DSA_TEST_SUITE)

$(BUILD_DIR)/$(DSA_TEST_SUITE): $(DSA_OBJS) $(UTILS_OBJS) | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(DSA_OBJS) $(UTILS_OBJS) -o $@

# standalones rules

$(STANDALONES_DIR): $(STANDALONE_TARGETS)

$(foreach target,$(STANDALONE_TARGETS),\
	$(eval $(target): $(BUILD_DIR)/$(target)))

$(BUILD_DIR)/%: $(SRC_DIR)/$(STANDALONES_DIR)/%.c $(UTILS_OBJS) | $(BUILD_DIR)
	@mkdir -p $(dir $@)
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

src-tree:
	@tree -a -I '.git|.gitignore|makefile|*.o|$(BUILD_DIR)'

.PHONY: clean clean-all src-tree
