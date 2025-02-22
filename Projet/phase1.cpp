#include <iostream>
#include <fstream> //module pour gestion de fichiers

// Fonctions à implémentées

// 1.
std::string parse_opcode(const std::string& instr) {

	std::string opcode;
	int i = 0;
	int s = instr.size();

	while(i < s &&  instr[i] != ' ') {
		opcode += instr[i];
		i++;
	}

	return opcode;
}


// 2.
uint16_t parse_operand(const std::string& instr) {

	uint16_t operand;
	int i = 0;
	int s = instr.size();

	while (i < s && instr[i] != ' ') {
		i++;
	}

	std::string op = instr.substr(i, s);

	if (!op.empty()) {

		operand = static_cast<uint16_t>(std::stoi(op));
	}

	return operand;

};

// 3.
void exec(const std::string& program_path) {

	//uint16_t registre = 0;

	std::ifstream file(program_path);

        std::string instr;

        while(getline(file, instr)) {
		std::string opcode = parse_opcode(instr);
		std::cout << opcode << std::endl;
		uint16_t operand = parse_operand(instr);
		std::cout << operand << std::endl;
	};

        file.close();

};

// Fonction Main
int main() {

	exec("program.txt");
	return 0;
}
