CXX = g++
CXXFLAGS = -Wall -std=c++17 -g
SRC = ./Calculator/calc.cpp ./Calculator/main.cpp ./Files/files.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = calc.out

all: $(OBJ)
	$(CXX) $^ -o $(TARGET)

.PHONY: clean
clean:
	rm -rf *.o *.dot *.png *.log
