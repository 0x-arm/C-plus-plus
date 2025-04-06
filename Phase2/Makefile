% : %.cpp
	g++ -Wall -Wextra -Wpedantic -std=c++23 $^ -o $@

test : tests2.py
	g++ -Wall -Wextra -Wpedantic -std=c++23 main.cpp memory.cpp -o main
	python3 tests2.py ./main
