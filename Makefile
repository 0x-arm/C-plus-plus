sum : sum.cpp
	g++ -Wall -Wextra sum.cpp -o sum
hello : hello.cpp
	g++ -Wall -Wextra hello.cpp -o hello

% : %.cpp
	g++ -Wall -Wextra $^ -o $@
