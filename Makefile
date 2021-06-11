CXX = g++
CXXFLAGS = -Wall -std=c++17 -g
SRC = ./Calculator/calc.cpp ./main.cpp ./Files/files.cpp ./Tree/node.cpp ./Differentiator/differentiator.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = diff.out

all: $(OBJ)
	$(CXX) $^ -o $(TARGET)
	rm -rf *.o *.dot

.PHONY: clean
clean:
	rm -rf *.o *.dot *.png *.log