EXEC := main
SRC := src
INC := includes

all:
	g++ -Wall -Wextra -Wpedantic -std=c++23 -I$(INC) $(SRC)/main.cpp $(SRC)/memory.cpp $(SRC)/instructions.cpp -o $(EXEC)

test: all
	python3 tests3.py ./$(EXEC)
