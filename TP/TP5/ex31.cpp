#include <iostream>

int main() {

	const unsigned N = 20;
	int Fibo[N] = {0, 1};

	for (unsigned i = 2; i < N; i++) {
		Fibo[i] = Fibo[i-1] + Fibo[i-2];
		std::cout << Fibo[i] << std::endl;
	}

	return 0;

}
