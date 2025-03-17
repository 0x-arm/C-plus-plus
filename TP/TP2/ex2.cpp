#include <iostream>

int main() {

	int a, b;

	std::cout << "introduisez un entier a : " << std::endl;
	std::cin >> a;

	std::cout << "introduisez un entier b : " << std::endl;
	std::cin >> b;

	if (b!=0 and not (a%b))
		std::cout << a << " est divisible par " << b << " et cela vaut : " << a/b << std::endl;

	else if (b!=0)
		std::cout << a << " n'est pas multiple de " << b << std::endl;

	else
		std::cout << " la division de " << a << " par " << b << " n'est pas un réel " << std::endl;

	return 0;
}



