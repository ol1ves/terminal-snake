CXX      := c++
CXXFLAGS := -std=c++17 -Wall -Wextra
LDLIBS   := -lncurses

BUILD    := build
TARGET   := $(BUILD)/terminal-snake
SRC      := main.cpp

$(TARGET): $(SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC) $(LDLIBS)

$(BUILD):
	mkdir -p $(BUILD)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD)

.PHONY: run clean
