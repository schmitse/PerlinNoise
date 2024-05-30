# Define the compiler
CXX = g++

# Define compiler flags
CXXFLAGS = -std=c++11 -Wall -Iinc -I/opt/homebrew/Cellar/cli11/2.4.2/include -I/opt/homebrew/Cellar/indicators/2.3/include -O3

# Define directories
SRC_DIR = src
INC_DIR = inc
TARGET_DIR = targets

# Define the target executable
TARGET = $(TARGET_DIR)/perlin

# Define the source files
SRCS = $(SRC_DIR)/Perlin.cpp $(SRC_DIR)/RandomVector.cpp $(TARGET_DIR)/perlin.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET_DIR) $(TARGET)

# Rule to create target directory if it doesn't exist
$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
