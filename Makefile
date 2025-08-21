# Stock Portfolio Tracker Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = portfolio_tracker
SOURCES = main.cpp Stock.cpp Transaction.cpp Portfolio.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✅ Build successful! Run with: ./$(TARGET)"

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "🧹 Cleaned build files"

# Rebuild everything
rebuild: clean all

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Show help
help:
	@echo "📋 Available targets:"
	@echo "  all     - Build the program (default)"
	@echo "  clean   - Remove build files"
	@echo "  rebuild - Clean and build"
	@echo "  debug   - Build with debug symbols"
	@echo "  run     - Build and run the program"
	@echo "  help    - Show this help message"

.PHONY: all clean rebuild debug run help
