#include <iostream> // module standard de C++
#include <fstream> // module pour la gestion de fichiers
#include <cmath> // module pour les fonctions mathématiques ( dans ce code : std::min()  et std::max() )
#include <vector> // module pour les vecteurs
#include <tuple> // module pour les tuples

uint16_t saturated(int n) {

    constexpr int MAX_UPPER_LIMIT = 65535; // Valeur maximale du registre
    uint16_t value = std::min(std::max(n, 0), MAX_UPPER_LIMIT);
	
	return value;

}

// Retourne les mots de l'instruction sous forme d'un vecteur
std::vector<std::string> parse_instr(const std::string& instr) {

    std::vector<std::string> elements;
    std::string value;
    int i = 0, s = instr.size();

    while (i <= s) {
        if (instr[i] == ' ' || instr[i] == '\0') {
            if (!value.empty()) {
                elements.push_back(value);
                value = "";
            }
        } 
        else {
            value += instr[i];
        }

		i++;
	}

    return elements;
}

// Retourne l'instruction sans les opérandes
std::string parse_opcode(const std::string& instr) {

	std::vector<std::string> elements = parse_instr(instr);
	std::string opcode = elements.at(0);

	return opcode;
}

// Retourne les opérandes (paramètres) sous forme de tuple de strings
std::tuple<std::string, std::string> parse_operands(const std::string& instr) {
    std::vector<std::string> elements = parse_instr(instr);
	int s = elements.size();

	for (int i = 0; i < elements.size(); i++) {
		std::cout << elements.at(i) << std::endl;
	}

    std::string operand1;
    std::string operand2;

	if (s > 1) {
        operand1 = elements.at(1);
    }

    if (s > 2) {
        operand2 = elements.at(2);
    }

    return {operand1, operand2};
}

// Exécute le programme dans le fichier texte' program_path'
void exec(const std::string& program_path) {

	static uint16_t registre = 0; // initialisation du registre
	static bool skip = false; // variable  nécessaire à l'instruction 'IFNZ'

	std::ifstream file(program_path);

        std::string instr;

	// Lecture du fichier tant que le fichier possède des lignes (lecture ligne par ligne)
        while(getline(file, instr)) {

		if (!skip) {

			std::string opcode = parse_opcode(instr);
			std::tuple<std::string, std::string> operand = parse_operands(instr);
			std::cout << opcode << " " << std::get<0>(operand) << " " << std::get<1>(operand) << std::endl;

			// Exécute l'opcode correspondant avec l'opérande associée et retourne 'skip' pour connaître l'état de la ligne suivante
			// if (instr == "IFNZ" && registre == 0) {
			// 	skip = true;
			// }
			// else if (instr == "SET") {
			// 	registre = operand;
			// }
			// else if (instr == "ADD") {
			// 	registre = saturated(registre + operand);
			// }
			// else if (instr == "SUB") {
			// 	registre = saturated(registre - operand);
			// }
			// else if (instr == "PRINT") {
			// 	std::cout << registre << std::endl;
			// }
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