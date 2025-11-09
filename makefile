# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Directories
SRC_DIR := src
MODEL_DIR := $(SRC_DIR)/model
VIEW_DIR := $(SRC_DIR)/view
CTRL_DIR := $(SRC_DIR)/controller

# Source files
SRCS := \
	$(SRC_DIR)/main.cpp \
	$(CTRL_DIR)/controller.cpp \
	$(MODEL_DIR)/alu.cpp \
	$(MODEL_DIR)/cpuModel.cpp \
	$(MODEL_DIR)/memory.cpp \
	$(MODEL_DIR)/registers.cpp \
	$(VIEW_DIR)/textView.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Output executable
TARGET := cpu_sim

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
