#include <iostream>

int main() {

	int v[5] = {0, 1, 2, 3, 4};

	for (int i = 0; i < 10000; i++) {
		std::cout << v[i] << std::endl;
	}

	return 0;
}
