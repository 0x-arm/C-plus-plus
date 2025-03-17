#include <iostream> // module standard de C++
#include <fstream> // module pour la gestion de fichiers
#include <cmath> // module pour les fonctions mathématiques ( dans ce code : std::min()  et std::max() )

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

// Exécute le programme contenu dans le fichier `program_path`
void exec(const std::string& program_path) {
    std::ifstream file(program_path);
    if (!file) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << program_path << std::endl;
        return;
    }

    uint16_t registre = 0;
    bool skip = false;
    std::string instr;

    while (std::getline(file, instr)) {
        if (!skip) {
            std::string opcode = parse_opcode(instr);
            uint16_t operand = parse_operand(instr);

            if (opcode == "IFNZ") {
                skip = (registre == 0);
            } else if (opcode == "SET") {
                registre = operand;
            } else if (opcode == "ADD") {
                registre = saturated(registre + operand);
            } else if (opcode == "SUB") {
                registre = saturated(registre - operand);
            } else if (opcode == "PRINT") {
                std::cout << registre << std::endl;
            }
        }
        skip = false;
    }
}

int main() {
    exec("program.txt");
    return 0;
}
