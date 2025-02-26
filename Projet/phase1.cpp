#include <iostream>
#include <fstream> //module pour gestion de fichiers
#include <cmath>

// Fonctions à implémentées

uint16_t registre = 0;
bool skip = false;


uint16_t saturated(int n) {

        return std::min(std::max(n, 0), static_cast<int>(65535));
}


// 1.
std::string parse_opcode(const std::string& instr) {

	std::string opcode;
	int i = 0, s = instr.size();

	while(i < s &&  instr[i] != ' ') {
		opcode += instr[i];
		i++;
	}

	return opcode;
}

// 2.
uint16_t parse_operand(const std::string& instr) {

	uint16_t operand;
	int i = 0, s = instr.size();

	while (i < s && instr[i] != ' ') {
		i++;
	}

	std::string op = instr.substr(i, s);

	if (!op.empty()) {

		operand = static_cast<uint16_t>(std::stoi(op));
	}

	return operand;

}

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

// 3.
void exec(const std::string& program_path) {

	std::ifstream file(program_path);

        std::string instr;

        while(getline(file, instr)) {

		if (skip) {
			skip = false;
			continue;
		}

		std::string opcode = parse_opcode(instr);

		uint16_t operand = parse_operand(instr);

		get_instr(opcode, operand);

	};

        file.close();

};

// Fonction Main
int main() {

	exec("program.txt");
	return 0;
}
