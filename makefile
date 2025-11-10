CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

SRC_DIR := src
MODEL_DIR := $(SRC_DIR)/model
VIEW_DIR := $(SRC_DIR)/view
CTRL_DIR := $(SRC_DIR)/controller

SRCS := \
	$(SRC_DIR)/main.cpp \
	$(CTRL_DIR)/controller.cpp \
	$(MODEL_DIR)/alu.cpp \
	$(MODEL_DIR)/cpuModel.cpp \
	$(MODEL_DIR)/memory.cpp \
	$(MODEL_DIR)/registers.cpp \
	$(VIEW_DIR)/textView.cpp

OBJS := $(SRCS:.cpp=.o)

TARGET := cpu_sim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
