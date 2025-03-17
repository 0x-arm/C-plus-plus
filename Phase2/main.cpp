#include <iostream> // module standard de C++
#include <fstream> // module pour la gestion de fichiers
#include <cmath> // module pour les fonctions mathématiques ( dans ce code : std::min()  et std::max() )

uint16_t registre = 0; // initialisation du registre
bool skip = false; // variable  nécessaire à l'instruction 'IFNZ'
constexpr int MAX_UPPER_LIMIT = 65535;


uint16_t saturated(int n) {

    uint16_t value = std::min(std::max(n, 0), MAX_UPPER_LIMIT);
	
	return value;

}

std::string parse_string(std::string instr, bool is_opcode = true) {

	std::string element;
	int i = 0, s = instr.size();

	while(i < s &&  instr[i] != ' ') {
		i++;
	}

	if(is_opcode) {
		element = instr.substr(0, i);
	}
	else {
		element = instr.substr(i, s);
	}

	return element;
}

// Retourne l'instruction sans les opérandes
std::string parse_opcode(const std::string& instr) {

	std::string opcode = parse_string(instr);
	return opcode;
}

// Retourne l'opérande (paramètre) sous forme numérique
uint16_t parse_operand(const std::string& instr) {

	std::string params = parse_string(instr, false);
	uint16_t operand;

	if (!params.empty()) {

		operand = static_cast<uint16_t>(std::stoi(params));
	}

	return operand;

}

// Exécute l'opcode correspondant avec l'opérande associée et retourne 'skip' pour connaître l'état de la ligne suivante
bool get_instr(std::string instr, uint16_t operand) {

	if (instr == "IFNZ" && registre == 0) {
                skip = true;
        }

	else if (instr == "SET") {
		registre = operand;
	}

	else if (instr == "ADD") {
		registre = saturated(registre + operand);
	}

	else if (instr == "SUB") {
		registre = saturated(registre - operand);
	}

	else if (instr == "PRINT") {
		std::cout << registre << std::endl;
	}

	return skip;
}

// Exécute le programme dans le fichier texte' program_path'
void exec(const std::string& program_path) {

	std::ifstream file(program_path);

        std::string instr;

	// Lecture du fichier tant que le fichier possède des lignes (lecture ligne par ligne)
        while(getline(file, instr)) {

		if (!skip) {

			std::string opcode = parse_opcode(instr);

			uint16_t operand = parse_operand(instr);

			get_instr(opcode, operand);
		}

		skip = false;
	};

        file.close();

};

// Fonction Main
int main() {

	exec("program.txt"); // Exécution du programme sur le fichier 'program.txt'
	return 0; // Retourne rien si tout est OK
}