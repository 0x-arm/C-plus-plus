#include "instructions.hpp"
#include <iostream>
#include <vector>

std::vector<std::string> parse_line(const std::string& instr) {

	// Vecteur pour contenir les mots de l'instruction
    std::vector<std::string> elements;

	// Variable pour stocker le mot en cours de traitement
    std::string value;

	// Variables utilisées pour le traitement de l'inscrution (indice = i, taille de l'instruction = s)
    int i = 0, s = instr.size();

	// Parcourir l'instruction
    while (i <= s) {

		// Si on trouve un espace ou la fin de l'instruction
        if (instr[i] == ' ' || instr[i] == '\0') {

			// Si le mot en cours de traitement n'est pas vide
            if (!value.empty()) {

				// Ajouter le mot au vecteur
                elements.push_back(value);

				// Réinitialiser le mot en cours de traitement
                value = "";
            }
        }
        else {

			// Sinon ajouter le caractère au mot en cours de traitement
            value += instr[i];
        }

		// Incrémenter pour passer au caractère suivant
		i++;
	}

	// Retourner le vecteur contenant les mots de l'instruction
    return elements;
}

std::string parse_opcode(const std::vector<std::string>& elements) {
	std::string opcode = elements.at(0);

	// Retourner l'opcode
	return opcode;
}


Opcode parse_opcode(const std::string& line) {

    std::vector<std::string> elements = parse_line(line);
    std::string opcode = elements.at(0);

    if (opcode == "SETv") return Opcode::SETv;
    if (opcode == "SETr") return Opcode::SETr;
    if (opcode == "ADDv") return Opcode::ADDv;
    if (opcode == "ADDr") return Opcode::ADDr;
    if (opcode == "SUBv") return Opcode::SUBv;
    if (opcode == "SUBr") return Opcode::SUBr;
}

Instruction::Instruction(const std::string& raw) : opcode(parse_opcode(raw)) {
    Opcode opcode = parse_opcode(raw);

    std::cout << "Opcode: " << opcode << std::endl;
}