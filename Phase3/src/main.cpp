#include <iostream> // module standard de C++
#include <fstream> // module pour la gestion de fichiers
#include <cmath> // module pour les fonctions mathématiques (dans ce code : std::min() et std::max())
#include <vector> // module pour les vecteurs

#include "Memory.hpp" // module pour la gestion de la mémoire
#include "Register.hpp" // module pour la gestion des registres
#include "Instructions.hpp" // module pour le traitement des instructions
#include "Saturated.hpp" // module pour appliquer la saturation sur les valeurs

// Exécute le programme dans le fichier texte 'program_path'
void exec(const std::string& program_path) {

	// Initialisation d’un vecteur de 4 registres
	std::vector<Register> registers(4);

	// Initialisation de la variable 'skip' à false (pour sauter l'instruction suivante si nécessaire)
	bool skip = false;

	// Ouverture du fichier contenant le programme
	std::ifstream file(program_path);

	// Définition de la variable pour stocker l’instruction lue
	std::string line;

	// Création de la mémoire avec une taille de 8 cases
	Memory mem(8);

	// Parcourir le fichier ligne par ligne
	while (getline(file, line)) {

		// Si l'instruction ne doit pas être passée (skip = false)
		if (!skip) {

			// Création d’un objet instruction à partir de la ligne
			Instruction instr(line);

			// Récupération des opérandes (pointeurs vers des objets Operand)
			const Operand* first_operand = instr.operands[0] ? instr.operands[0] : nullptr;
			const Operand* second_operand = instr.operands[1] ? instr.operands[1] : nullptr;

			// Vérification de l’opcode pour exécuter l’instruction correspondante
			switch (instr.opcode) {

				// Si l’opcode est IFNZ
				case Opcode::IFNZ:

					// Si la valeur du registre est 0, activer le saut de la prochaine instruction
					if (registers[instr.operands[0]->parsed] == 0) {
						skip = true;
					}
					break;

				// Si l’opcode est PRINT
				case Opcode::PRINT:

					// Si le premier opérande est un registre et qu’il n’y a pas de second opérande
					if (first_operand->type == OperandType::REGISTER && second_operand == 0) {

						// Afficher la valeur du registre
						std::cout << registers[instr.operands[0]->parsed] << std::endl;
					}
					break;

				// Si l’opcode est SETv (affectation directe d’une valeur dans un registre)
				case Opcode::SETv:

					// Vérifier que le premier opérande est un registre et le second une valeur
					if (first_operand->type == OperandType::REGISTER && second_operand->type == OperandType::NUMERIC) {

						// Récupérer l’index du registre et la valeur
						int reg_index = first_operand->parsed;
						int value = second_operand->parsed;

						// Affecter la valeur saturée au registre
						registers[reg_index] = saturated(value);
					}
					break;

				// Si l’opcode est SETr (copie de registre à registre)
				case Opcode::SETr:

					// Vérifier que les deux opérandes sont des registres
					if (first_operand->type == OperandType::REGISTER && second_operand->type == OperandType::REGISTER) {

						// Récupérer les index des deux registres
						int reg_1 = first_operand->parsed;
						int reg_2 = second_operand->parsed;

						// Copier la valeur du second registre dans le premier
						registers[reg_1] = registers[reg_2];
					}
					break;

				// Si l’opcode est ADDv (addition registre + valeur)
				case Opcode::ADDv:

					// Vérifier que le premier opérande est un registre et le second une valeur
					if (first_operand->type == OperandType::REGISTER && second_operand->type == OperandType::NUMERIC) {

						// Récupérer l’index du registre et la valeur
						int reg_index = first_operand->parsed;
						int value = second_operand->parsed;

						// Additionner et affecter la valeur saturée dans le registre
						registers[reg_index] = saturated(registers[reg_index] + value);
					}
					break;

				// Si l’opcode est ADDr (addition registre + registre)
				case Opcode::ADDr:

					// Vérifier que les deux opérandes sont des registres
					if (first_operand->type == OperandType::REGISTER && second_operand->type == OperandType::REGISTER) {

						// Récupérer les index des deux registres
						int reg_1 = first_operand->parsed;
						int reg_2 = second_operand->parsed;

						// Additionner et affecter la valeur saturée dans le premier registre
						registers[reg_1] = saturated(registers[reg_1] + registers[reg_2]);
					}
					break;

				// Si l’opcode est SUBv (soustraction registre - valeur)
				case Opcode::SUBv:

					// Vérifier que le premier opérande est un registre et le second une valeur
					if (first_operand->type == OperandType::REGISTER && second_operand->type == OperandType::NUMERIC) {

						// Récupérer l’index du registre et la valeur
						int reg_index = first_operand->parsed;
						int value = second_operand->parsed;

						// Soustraire et affecter la valeur saturée dans le registre
						registers[reg_index] = saturated(registers[reg_index] - value);
					}
					break;

				// Si l’opcode est SUBr (soustraction registre - registre)
				case Opcode::SUBr:

					// Vérifier que les deux opérandes sont des registres
					if (first_operand->type == OperandType::REGISTER && second_operand->type == OperandType::REGISTER) {

						// Récupérer les index des deux registres
						int reg_1 = first_operand->parsed;
						int reg_2 = second_operand->parsed;

						// Soustraire et affecter la valeur saturée dans le premier registre
						registers[reg_1] = saturated(registers[reg_1] - registers[reg_2]);
					}
					break;

				// Si l’opcode est STORE
				case Opcode::STORE:

					// Vérifier que le premier opérande est une valeur et le second un registre
					if (first_operand->type == OperandType::NUMERIC && second_operand->type == OperandType::REGISTER) {

						// Récupérer l’adresse mémoire et l’index du registre
						uint16_t address = first_operand->parsed;
						uint16_t reg_index = second_operand->parsed;

						// Stocker la valeur du registre à l’adresse mémoire (valeur saturée)
						mem[address] = saturated(registers[reg_index]);
					}
					break;

				// Si l’opcode est LOAD
				case Opcode::LOAD:

					// Vérifier que le premier opérande est une valeur et le second un registre
					if (first_operand->type == OperandType::NUMERIC && second_operand->type == OperandType::REGISTER) {

						// Récupérer l’adresse mémoire et l’index du registre
						uint16_t address = first_operand->parsed;
						uint16_t reg_index = second_operand->parsed;

						// Charger la valeur depuis la mémoire dans le registre (valeur saturée)
						registers[reg_index] = saturated(mem[address]);
					}
					break;

				// Si l’opcode est PUSH
				case Opcode::PUSH:

					// Vérifier qu'il n'y a qu'un seul opérande et que celui-ci est un registre
					if (first_operand->type == OperandType::REGISTER && second_operand == 0) {

						// Récupérer l’index du registre
						uint16_t reg_index = first_operand->parsed;

						// Pousser la valeur du registre (saturée) sur la pile
						mem.push(saturated(registers[reg_index]));
					}
					break;

				// Si l’opcode est POP
				case Opcode::POP:

					// Vérifier qu'il n'y a qu'un seul opérande et que celui-ci est un registre
					if (first_operand->type == OperandType::REGISTER && second_operand == 0) {

						// Récupérer l’index du registre
						uint16_t reg_index = first_operand->parsed;

						// Retirer la dernière valeur de la pile et l’affecter au registre (valeur saturée)
						registers[reg_index] = saturated(mem.pop());
					}
					break;

				// Opcode non reconnu
				default:

					// Quitter le programme si aucun Opcode n'est reçu
					std::exit(1);
					break;
			}
		}

		// Si l’instruction n’est pas lue (skip = true)
		else {

			// Réinitialisation de la variable 'skip' pour la prochaine instruction
			skip = false;
		};
	};

	// Fermeture du fichier
	file.close();
}

// Fonction Main
int main() {

	// Exécution du programme sur le fichier 'program.txt'
	exec("program.txt");

	return 0; // Retourne rien si tout est OK
}
