#include <iostream> // module standard de C++
#include <fstream> // module pour la gestion de fichiers
#include <cmath> // module pour les fonctions mathématiques ( dans ce code : std::min()  et std::max() )
#include <vector> // module pour les vecteurs
#include <tuple> // module pour les tuples
#include <cctype>
#include <unordered_map>
#include "memory.hpp" // module pour la gestion de la mémoire

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

    static std::string first_operand;
    static std::string second_operand;

	if (s > 1) {
        first_operand = elements.at(1);
		
		if (s > 2) {
			second_operand = elements.at(2);
		}
    }
	
    return {first_operand, second_operand};
}

// Exécute l'instruction
void exec_instr(const std::string& opcode, const std::string& first_operand, const std::string& second_operand, std::unordered_map<std::string, int>& registers, bool& skip) {

	if (opcode == "IFNZ") {
		if (registers[first_operand] == 0) {
			skip = true;
		}
	}

	else if (opcode == "SET") {
		if (std::isdigit(second_operand[0])) {
			registers[first_operand] = std::stoi(second_operand);
		}
		else {
			registers[first_operand] = registers[second_operand];
		}
	}

	else if (opcode == "ADD") {
		if (std::isdigit(second_operand[0])) {
			registers[first_operand] = saturated(registers[first_operand] + std::stoi(second_operand));
		}
		else {
			registers[first_operand] = saturated(registers[first_operand] + registers[second_operand]);
		}

		std::cout << registers[first_operand] << std::endl; // Affiche la valeur du registre après l'addition
	}

	else if (opcode == "SUB") {
		if (std::isdigit(second_operand[0])) {
			registers[first_operand] = saturated(registers[first_operand] - std::stoi(second_operand));
		}
		else {
			registers[first_operand] = saturated(registers[first_operand] - registers[second_operand]);
		}
	}

	else if (opcode == "PRINT") {
		std::cout << registers[first_operand] << std::endl;
	}

	else if (opcode == "STORE") {
		if (std::isdigit(first_operand[0])) {
			uint8_t address = std::stoi(first_operand);
			write(address, registers[second_operand]);
		}
	}

	else if (opcode == "LOAD") {
		if (std::isdigit(first_operand[0])) {
			uint8_t address = std::stoi(first_operand);
			uint16_t data = read(address);
			registers[second_operand] = data;
		}
	}

	else if (opcode == "PUSH") {
		if (std::isalpha(first_operand[0])) {
			uint16_t value = registers[first_operand];
			push(value);
		}
	}

	else if (opcode == "POP") {
		if (std::isalpha(first_operand[0])) {
			uint16_t data = pop();
			registers[first_operand] = data;
		}
	}

}

// Exécute le programme dans le fichier texte' program_path'
void exec(const std::string& program_path) {

	static std::unordered_map<std::string, int> registers = {
		{"a", 0},
		{"b", 0},
		{"c", 0},
		{"d", 0}
	}; // initialisation du registre

	static bool skip = false; // variable nécessaire à l'instruction 'IFNZ'

	static std::ifstream file(program_path);

    std::string instr;

    while (getline(file, instr)) {

		if (!skip) {

			std::string opcode = parse_opcode(instr);
			std::tuple<std::string, std::string> operand = parse_operands(instr);

			std::string first_operand = std::get<0>(operand);
			std::string second_operand = std::get<1>(operand);

			exec_instr(opcode, first_operand, second_operand, registers, skip); // exécution de l'instruction

		}

		else {
			skip = false; // réinitialisation de la variable 'skip' pour la prochaine instruction
		};

	};

	file.close();
}

// Fonction Main
int main() {

	exec("program.txt"); // Exécution du programme sur le fichier 'program.txt'
	return 0; // Retourne rien si tout est OK
}