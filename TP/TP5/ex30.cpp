#include <iostream>

int main() {

	int n; std::cin >> n;
	int* p = &n;
	std::cout << "Nombre : " << n << " | " << "Adresse de stockage :" << p << std::endl;

	return 0;

}
