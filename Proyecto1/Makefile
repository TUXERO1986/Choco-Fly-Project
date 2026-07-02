
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wno-return-type
TARGET   := app_vuelos

SRCS := $(wildcard *.cpp)

ifeq ($(OS), Windows_NT)
    TARGET  := $(TARGET).exe
    RM      := del /Q
else
    RM      := rm -f
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
	@echo "===> Compilacion exitosa: $(TARGET)"

clean:
	$(RM) $(TARGET)

run: $(TARGET)
ifeq ($(OS), Windows_NT)
	$(TARGET)
else
	./$(TARGET)
endif

.PHONY: all clean run