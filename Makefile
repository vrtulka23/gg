DIR_SOURCE = src
DIR_BUILD = build

CC := g++
CFLAGS := -Wall -std=c++20 -g
TARGET := gg

SRCS := $(wildcard $(DIR_SOURCE)/*.cpp)
_OBJS := $(patsubst %.cpp,%.o,$(SRCS))
OBJS = ${subst $(DIR_SOURCE),$(DIR_BUILD),$(_OBJS)}

all: directories $(TARGET)

directories:
	mkdir -p $(DIR_BUILD)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

$(DIR_BUILD)/%.o: $(DIR_SOURCE)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(DIR_BUILD)

.PHONY: all clean
