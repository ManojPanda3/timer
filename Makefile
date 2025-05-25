CC = clang
BUILD_DIR = build
SRC_FILES = src/*.c
TARGET = $(BUILD_DIR)/timer

CFLAGS = -Wall -Wextra -std=c11 -Iheader
CLANGD_FILE = compile_commands.json

.PHONY: all clean run clangd_gen

all: $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(SRC_FILES) | $(BUILD_DIR)
	@echo "Building $(TARGET)..."
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)

run: $(TARGET)
	@echo "Running $(TARGET)..."
	@./$(TARGET)

clangd_gen:
	@echo "Generating $(CLANGD_FILE) for clangd..."
	@if ! command -v bear &> /dev/null; then \
		echo "Error: 'bear' command not found. Please install it (e.g., 'sudo apt install bear' or 'brew install bear')."; \
		exit 1; \
	fi
	@bear -- $(MAKE) $(TARGET)

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@rm -f $(CLANGD_FILE)
