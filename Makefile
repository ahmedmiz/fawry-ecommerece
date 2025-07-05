# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src
DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O2 -DNDEBUG

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = $(SRC_DIR)/tests

# Source files
SOURCES = $(shell find $(SRC_DIR) -name "*.cpp" ! -path "$(TEST_DIR)/*")
TEST_SOURCES = $(shell find $(TEST_DIR) -name "*.cpp")
HEADERS = $(shell find $(SRC_DIR) -name "*.h")

# Object files
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:%.cpp=$(BUILD_DIR)/%.o)

# Executables
TARGET = fawry-eCommerce
TEST_TARGET = $(TARGET)_tests

# Default target
all: debug

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(BUILD_DIR)/$(TARGET)

# Release build
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(BUILD_DIR)/$(TARGET)

# Main executable
$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJECTS) -o $@

# Test executable
$(BUILD_DIR)/$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJECTS) $(TEST_OBJECTS) -o $@

# Compile source files
$(BUILD_DIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run tests
test: $(BUILD_DIR)/$(TEST_TARGET)
	./$(BUILD_DIR)/$(TEST_TARGET)

# Run main program
run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Install dependencies (for macOS)
install-deps:
	@echo "Installing dependencies..."
	@if [ "$(shell uname)" = "Darwin" ]; then \
		echo "macOS detected. Make sure you have Xcode Command Line Tools installed:"; \
		echo "xcode-select --install"; \
	fi

# Help
help:
	@echo "Available targets:"
	@echo "  all        - Build debug version (default)"
	@echo "  debug      - Build with debug flags"
	@echo "  release    - Build with release flags"
	@echo "  test       - Build and run tests"
	@echo "  run        - Build and run main program"
	@echo "  clean      - Remove build files"
	@echo "  install-deps - Install dependencies"
	@echo "  help       - Show this help"

.PHONY: all debug release test run clean install-deps help
