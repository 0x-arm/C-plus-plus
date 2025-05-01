#include <iostream> // module standard de C++
#include <fstream> // module pour la gestion de fichiers
#include <cmath> // module pour les fonctions mathématiques ( dans ce code : std::min()  et std::max() )
#include <vector> // module pour les vecteurs

// #include "memory.hpp" // module pour la gestion de la mémoire (importation de la mémoire dans le fichier 'memory.hpp')
// #include "register.hpp" // module pour la gestion des registres (importation des registres dans le fichier 'register.hpp')
#include "instructions.hpp" // module pour la gestion des instructions (importation des instructions dans le fichier 'instructions.hpp')

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

//// Retourne l'instruction sans les opérandes
std::string parse_opcode(const std::vector<std::string>& elements) {
	// Le premier mot de du vecteur est l'opcode
	std::string opcode = elements.at(0);

	// Retourner l'opcode
	return opcode;
}

// Exécute le programme dans le fichier texte' program_path'
void exec(const std::string& program_path) {

	// Initialisation de la variable 'skip' à false (pour sauter l'instruction suivante si nécessaire)
	bool skip = false;

	// Ouverture du fichier contenant le programme
	std::ifstream file(program_path);

	// Définition de la variable pour stocker l'instruction lue
    std::string instr;

	// Memory memory;

	// Parcourir le fichier ligne par ligne
    while (getline(file, instr)) {


		// Si l'instruction ne doit pas être passée (skip = false)
		if (!skip) {

			// Récupérer les éléments de l'instruction
			std::vector<std::string> elements = parse_line(instr);

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