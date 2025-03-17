#include <iostream> // module standard de C++
#include <fstream> // module pour la gestion de fichiers
#include <cmath> // module pour les fonctions mathématiques ( dans ce code : std::min()  et std::max() )

uint16_t registre = 0; // initialisation du registre
bool skip = false; // variable  nécessaire à l'instruction 'IFNZ'

// Retourne la valeur non signée et saturée de 16 bits d'un nombre entier
uint16_t saturated(int n) {

        return std::min(std::max(n, 0), 65535); // Implémentation donnée dans le document PDF
}


// Retourne l'instruction sans les opérandes
std::string parse_opcode(const std::string& instr) {

	std::string opcode; // Initialisation de la variable 'opcode' de type chaine de caractères
	int i = 0, s = instr.size(); // Initialisation de l'indice 'i' et la taille 's' de la chaine de caractères 'instr' de type entier

	// Récupération de chaque caractères de la ligne donnée (instr) jusqu'à soit un espace ' ' qui sépare un opcode et une opérande soit la fin de l'instruction si celle-ci ne possède pas d'opérande
	while(i < s &&  instr[i] != ' ') {
		opcode += instr[i]; // Les caractères additionnés à l'opcode (variable) correspondent à chaque lettres de l'opcode (chaine de caractères) provenant de l'instruction (paramètre instr)
		i++;
	}

	return opcode;
}

// Retourne l'opérande (paramètre) sous forme numérique
uint16_t parse_operand(const std::string& instr) {

	uint16_t operand; // Initialisation de la variable 'operand' de type entier non signé de 16 bits
	int i = 0, s = instr.size(); // Initialisation de l'indice 'i' et la taille 's' de la chaine de caractères 'instr' de type entier

	// Récupération de la position de l'espace ' ' dans la chaine de caractères instr si il y en a un pour sélectionner seulement la partie avec l'opérande s'il y en a un, sinon, la position est nulle
	while (i < s && instr[i] != ' ') {
		i++;
	}

	std::string op = instr.substr(i, s); // Récupération de l'opérande sous forme de chaine de caractères à partir de la position de l'espace ' ' jusqu'au dernier caractère dans la chaine de caractères instr

	// Vérifier si l'opérande récupérée sous forme de chaine de caractères n'est pas une chaine vide
	if (!op.empty()) {

		operand = static_cast<uint16_t>(std::stoi(op)); // Conversion de la chaine de caractères représentant l'opérande en entier non signé de 16 bits si la condition est vérifiée
	}

	return operand;

}

// Exécute l'opcode correspondant avec l'opérande associée et retourne 'skip' pour connaître l'état de la ligne suivante
bool get_instr(std::string instr, uint16_t operand) {

	if (instr == "IFNZ" && registre == 0) {
                skip = true; // Mise à jour de la variable 'skip' si la condition est vérifiée (false -> true)
        }

	else if (instr == "SET") {
		registre = operand; // Opération d'affectation la valeur de l'opérande à la valeur du registre (initialement à 0)
	}

	else if (instr == "ADD") {
		registre = saturated(registre + operand); // Opération d'addition entre le registre et l'opérande + saturation du résultat
	}

	else if (instr == "SUB") {
		registre = saturated(registre - operand); // Opération de soustraction entre le registre et l'opérande + saturation du résultat
	}

	else if (instr == "PRINT") {
		std::cout << registre << std::endl; // Afficher la valeur du registre
	}

	return skip;
}

// Exécute le programme dans le fichier texte' program_path'
void exec(const std::string& program_path) {

	std::ifstream file(program_path); // Ouverture du fichier 'program_path'

        std::string instr; // Initialisation de la variable 'instr' de type chaine de caractères

	// Lecture du fichier tant que le fichier possède des lignes (lecture ligne par ligne)
        while(getline(file, instr)) {

		if (skip) {
			skip = false; // Réinitialiser la variable 'skip' pour le prochain tour de boucle
			continue; // Ignorer l'instruction suivante si la variable 'skip' est à true
		}

		std::string opcode = parse_opcode(instr); // Affecter la valeur résultante de la lecture de l'opcode dans instr à la variable 'opcode'

		uint16_t operand = parse_operand(instr); // Affecter la valeur résultante de la lecture de l'operande dans instr à la variable 'operand'

		get_instr(opcode, operand); // Exécuter l'instruction instr au complet en fonction de l'opcode et l'opérande fournies

	};

        file.close(); // Fermeture du fichier

};

// Fonction Main
int main() {

	exec("program.txt"); // Exécution du programme sur le fichier 'program.txt'
	return 0; // Retourne rien si tout est OK
}
