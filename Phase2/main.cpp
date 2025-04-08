#include <iostream> // module standard de C++
#include <fstream> // module pour la gestion de fichiers
#include <cmath> // module pour les fonctions mathématiques ( dans ce code : std::min()  et std::max() )
#include <vector> // module pour les vecteurs
#include <tuple> // module pour les tuples
#include <cctype> // module pour la gestion des caractères (dans ce code : std::isdigit() et std::isalpha())
#include <unordered_map> // module pour le dictionnaire des registres (dans ce code : std::unordered_map<std::string, int>)
#include "Memory.hpp" // module pour la gestion de la mémoire (importation de la mémoire dans le fichier 'memory.hpp')

// Valeur maximale du registre
constexpr int MAX_UPPER_LIMIT = 65535;

//// Retourne la valeur saturée d'un entier
uint16_t saturated(int n) {

	// Saturation de la valeur
    uint16_t value = std::min(std::max(n, 0), MAX_UPPER_LIMIT); 
	
	// Retourner la valeur saturée
	return value;

}


//// Retourne les mots de l'instruction sous forme d'un vecteur
std::vector<std::string> parse_instr(const std::string& instr) {

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


//// Retourne l'instruction sans les opérandes
std::string parse_opcode(const std::vector<std::string>& elements) {

	// Le premier mot de du vecteur est l'opcode
	std::string opcode = elements.at(0);

	// Retourner l'opcode
	return opcode;
}


//// Retourne les opérandes (paramètres) sous forme de tuple de strings
std::tuple<std::string, std::string> parse_operands(const std::vector<std::string>& elements) {

	// Récuperer le nombre d'éléments dans le vecteur
	int s = elements.size();

	// Définitions des variables pour stocker les opérandes
    static std::string first_operand;
    static std::string second_operand;

	// Si le vecteur contient au moins 2 éléments, on récupère les opérandes
	if (s > 1) {

		// Récupérer le premier opérande
        first_operand = elements.at(1);
		
		// Si le vecteur contient au moins 3 éléments, on récupère le deuxième opérande
		if (s > 2) {

			// Récupérer le deuxième opérande
			second_operand = elements.at(2);
		}
    }
	
	// Retourner les opérandes sous forme de tuple
    return {first_operand, second_operand};
}


//// Exécute les instructions de bases
void basic_instr(const std::string& opcode, const std::string& first_operand, const std::string& second_operand, std::unordered_map<std::string, int>& registers, bool& skip) {

	// Si l'opcode est IFNZ
	if (opcode == "IFNZ") {

		// Vérifier si le registre est égal à 0
		if (registers[first_operand] == 0) {

			// Si oui, on saute l'instruction suivante (skip = true)
			skip = true;
		}
	}

	// Si l'opcode est SET
	else if (opcode == "SET") {

		// Si le premier opérande est une valeur
		if (std::isdigit(second_operand[0])) {

			// Convertir en entier et le stocker dans le registre
			registers[first_operand] = saturated(std::stoi(second_operand));
		}

		// Sinon le premier opérande est un registre
		else {

			// Copier la valeur du registre dans l'autre registre
			registers[first_operand] = saturated(registers[second_operand]);
		}
	}

	// Si l'opcode est ADD
	else if (opcode == "ADD") {

		// Si le second opérande est une valeur
		if (std::isdigit(second_operand[0])) {

			// Additioner la valeur avec le registre donnant un résultat saturé et mettre à jour le registre par ce résultat
			registers[first_operand] = saturated(registers[first_operand] + std::stoi(second_operand));
		}

		// Sinon le second opérande est un registre
		else {

			// Additioner les deux registres donnant un résultat saturé et mettre à jour le premier registre par ce résultat
			registers[first_operand] = saturated(registers[first_operand] + registers[second_operand]);
		}
	}

	// Si l'opcode est SUB
	else if (opcode == "SUB") {

		// Si le second opérande est une valeur
		if (std::isdigit(second_operand[0])) {

			// Soustraire la valeur avec le registre donnant un résultat saturé et mettre à jour le registre par ce résultat
			registers[first_operand] = saturated(registers[first_operand] - std::stoi(second_operand));
		}

		// Sinon le second opérande est un registre
		else {

			// Soustraire les deux registres donnant un résultat saturé et mettre à jour le premier registre par ce résultat
			registers[first_operand] = saturated(registers[first_operand] - registers[second_operand]);
		}
	}

	// Si l'opcode est PRINT
	else if (opcode == "PRINT") {

		// Afficher la valeur du registre
		std::cout << registers[first_operand] << std::endl;
	}

}

// Exécute les instructions liées à la mémoire
void memory_instr (const std::string& opcode, const std::string& first_operand, const std::string& second_operand, std::unordered_map<std::string, int>& registers, Memory& memory) {
	
	// Si l'opcode est STORE
	if (opcode == "STORE") {

		// Si le premier opérande est une valeur
		if (std::isdigit(first_operand[0])) {

			// Convertir le premier opérande en entier non signé de 8 bits, qui repésente l'adresse mémoire
			uint8_t address = std::stoi(first_operand);

			// Ecriture de la valeur dans l'adresse mémoire
			memory.write(address, registers[second_operand]);
		}
	}

	// Si l'opcode est LOAD
	else if (opcode == "LOAD") {

		// Si le premier opérande est une valeur
		if (std::isdigit(first_operand[0])) {

			// Convertir le premier opérande en entier non signé de 8 bits, qui repésente l'adresse mémoire
			uint8_t address = std::stoi(first_operand);

			// Lire la valeur de l'adresse mémoire et récupérer cette valeur
			uint16_t data = memory.read(address);

			// Stocker la valeur dans le registre
			registers[second_operand] = data;
		}
	}

	// Si l'opcode est PUSH
	else if (opcode == "PUSH") {

		// Si le premier opérande est un charactère
		if (std::isalpha(first_operand[0])) {

			// Convertir le registre en entier non signé de 16 bits
			uint16_t value = registers[first_operand];

			// Push la valeur sur la pile
			memory.push(value);
		}
	}

	// Si l'opcode est POP
	else if (opcode == "POP") {

		// Si le premier opérande est un charactère
		if (std::isalpha(first_operand[0])) {
			// Pop la valeur de la pile et récupérer cette valeur
			uint16_t data = memory.pop();

			// Stocker la valeur dans le registre
			registers[first_operand] = data;
		}
	}
}


// Exécute le programme dans le fichier texte' program_path'
void exec(const std::string& program_path) {

	// Initialisation des registres (a, b, c, d) à 0
	std::unordered_map<std::string, int> registers = {
		{"a", 0},
		{"b", 0},
		{"c", 0},
		{"d", 0}
	};

	// Initialisation de la variable 'skip' à false (pour sauter l'instruction suivante si nécessaire)
	bool skip = false;

	// Ouverture du fichier contenant le programme
	std::ifstream file(program_path);

	// Définition de la variable pour stocker l'instruction lue
    std::string instr;

	Memory memory;

	// Parcourir le fichier ligne par ligne
    while (getline(file, instr)) {


		// Si l'instruction ne doit pas être passée (skip = false)
		if (!skip) {

			// Récupérer les éléments de l'instruction
			std::vector<std::string> elements = parse_instr(instr);

			// Récupération de l'opcode
			std::string opcode = parse_opcode(elements);

			// Récupération des opérandes
			std::tuple<std::string, std::string> operands = parse_operands(elements);

			std::string first_operand = std::get<0>(operands);
			std::string second_operand = std::get<1>(operands);

			// Exécuter l'instruction
			// Si l'instruction est une instruction mémoire (STORE, LOAD, PUSH, POP)
			if (opcode == "STORE" || opcode == "LOAD" || opcode == "PUSH" || opcode == "POP") {
				// Exécuter l'instruction mémoire
				memory_instr(opcode, first_operand, second_operand, registers, memory);
			} 
			else {
				// Exécuter l'instruction basique
				basic_instr(opcode, first_operand, second_operand, registers, skip);
			}

		}

		// Si l'instruction l'instruction n'est pas lue (skip = true)
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