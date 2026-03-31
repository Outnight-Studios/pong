#Project Configuration
TARGET        = pong
CC            = cc
SRC_DIR       = ./src
INC_DIR       = ./inc
OBJ_DIR       = ./obj
BIN_DIR       = ./bin

#Parallel jobs: try nproc, then getconf, then /dev/cpu count (Linux), then default to 1
NPROC         := $(shell nproc 2>/dev/null || getconf _NPROCESSORS_ONLN || ls /dev/cpu/ | wc -l || echo 1)
MAKEFLAGS     += -j$(NPROC)

#Find all files matching a pattern recursively: $(call rwildcard,<dir>,<pattern>)
rwildcard     = $(foreach d,$(wildcard $(addsuffix /*,$1)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

#File Discovery
SRCS          = $(call rwildcard,$(SRC_DIR),*.c)

#Per-build object lists (each build has its own subdirectory)
DEBUG_OBJS    = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/debug/%.o,$(SRCS))
RELEASE_OBJS  = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/release/%.o,$(SRCS))
NATIVE_OBJS   = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/native/%.o,$(SRCS))

#Compiler Flags
COMMON_FLAGS  = -I$(abspath $(INC_DIR)) -Wall -Wextra -Wpedantic -fdiagnostics-color=always -lSDL3
DEBUG_FLAGS   = -Og -ggdb3
RELEASE_FLAGS = -O3 -flto -mtune=generic
NATIVE_FLAGS  = -O3 -flto -march=native

#Debug build
debug: CFLAGS = $(COMMON_FLAGS) $(DEBUG_FLAGS)
debug: $(BIN_DIR)/$(TARGET)-debug

#Release build
release: CFLAGS = $(COMMON_FLAGS) $(RELEASE_FLAGS)
release: $(BIN_DIR)/$(TARGET)-release

#Native build
native: CFLAGS = $(COMMON_FLAGS) $(NATIVE_FLAGS)
native: $(BIN_DIR)/$(TARGET)-native

#Compile objects - auto-generate dependency files with -MMD -MP
$(OBJ_DIR)/debug/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -c $< -o $@

$(OBJ_DIR)/release/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -c $< -o $@

$(OBJ_DIR)/native/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -c $< -o $@

#Main targets
$(BIN_DIR):
	@mkdir -p $@

$(BIN_DIR)/$(TARGET)-debug: $(DEBUG_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/$(TARGET)-release: $(RELEASE_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/$(TARGET)-native: $(NATIVE_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

#Include auto-generated header dependency files
-include $(DEBUG_OBJS:.o=.d)
-include $(RELEASE_OBJS:.o=.d)
-include $(NATIVE_OBJS:.o=.d)

init:
	mkdir -p $(SRC_DIR) $(INC_DIR)

#Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

#Initialise .clangd to see `./inc/`
clangd:
	@echo "CompileFlags:" > .clangd
	@echo "  Add:" >> .clangd
	@for flag in $(COMMON_FLAGS); do echo "    - $$flag" >> .clangd; done

#Help message
help:
	@echo "Available targets:"
	@echo "  init     : Initialises Source and Include directories"
	@echo "  debug    : Build debug version"
	@echo "  release  : Build release version"
	@echo "  native   : Build with native CPU optimizations"
	@echo "  clean    : Remove all build artifacts"
	@echo "  clangd   : Initialises .clangd file"
	@echo "  help     : Show this help message"
	@echo ""
	@echo "Binaries output to: $(BIN_DIR)"
	@echo "Objects output to: $(OBJ_DIR)"

.PHONY: init debug release native clean clangd help
