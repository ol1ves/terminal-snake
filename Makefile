CXX      := c++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
LDLIBS   := -lncurses

BUILD    := build
TARGET   := $(BUILD)/terminal-snake
SRC      := main.cpp util.cpp
OBJ      := $(SRC:%.cpp=$(BUILD)/%.o)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDLIBS)

$(BUILD)/%.o: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD)

.PHONY: run clean
