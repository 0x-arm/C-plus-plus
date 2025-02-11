#include <iostream>
#include <cmath>

int main() {

	double x = 0;
	int i = 0;
	while(i < 100'000'000) {
	++i;
	x += std::cout << sqrt(i);
	}

	std::cout << x << std::endl;
	return 0;
};
