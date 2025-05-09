#include "Instructions.hpp" // module contenant les définitions liées aux instructions
#include "Register.hpp" // module contenant la définition des registres
#include <iostream> // module standard pour l'affichage
#include <vector> // module pour utiliser des vecteurs
#include <cctype> // module pour gérer les caractères (dans ce code : std::isalpha())
#include <map> // module pour la structure de données map

//// Découpe une ligne brute en éléments (mots)
std::vector<std::string> parse_line(const std::string& raw) {
    
    // Vecteur pour contenir les éléments extraits
    std::vector<std::string> elements;

    // Variable pour stocker un mot temporairement
    std::string value;

    // Parcourir chaque caractère de la ligne
    for (char c : raw) {

        // Si on trouve un espace
        if (c == ' ') {

            // Si le mot temporaire n'est pas vide
            if (!value.empty()) {

                // Ajouter le mot au vecteur
                elements.push_back(value);

                // Réinitialiser le mot temporaire
                value.clear();
            }
        }

        // Sinon, ajouter le caractère au mot
        else {
            value += c;
        }
    }

    // Ajouter le dernier mot s’il n’est pas vide
    if (!value.empty()) {
        elements.push_back(value);
    }

    // Retourner le vecteur contenant les éléments
    return elements;
}


//// Convertit une chaîne d'opcode en type énuméré Opcode
Opcode parse_opcode(const std::vector<std::string>& raw) {
    
    // Récupérer le premier mot (l’opcode)
    std::string opcode = raw[0];

    // Vérifier la correspondance de l’opcode avec les types définis
    if (opcode == "SETv") return SETv;
    else if (opcode == "SETr") return SETr;
    else if (opcode == "ADDv") return ADDv;
    else if (opcode == "ADDr") return ADDr;
    else if (opcode == "SUBv") return SUBv;
    else if (opcode == "SUBr") return SUBr;
    else if (opcode == "IFNZ") return IFNZ;
    else if (opcode == "PRINT") return PRINT;
    else if (opcode == "STORE") return STORE;
    else if (opcode == "LOAD") return LOAD;
    else if (opcode == "PUSH") return PUSH;
    else if (opcode == "POP") return POP;

    // Si l’opcode n’est pas reconnu, lancer une exception
    throw std::invalid_argument("Opcode invalide");
}


//// Convertit un mot en opérande de type Operand
Operand* parse_operand(const std::vector<std::string>& raw, const int index, std::map<std::string, int>& registers_id) {

    // Récupérer la taille du vecteur
    int size = raw.size();

    // Vérifier si l’index est hors limites
    if (index >= size) {
        return nullptr; // Aucun opérande à cet emplacement
    }

    // Récupérer la valeur à l’index donné
    std::string value = raw[index];

    // Si la valeur est vide, retourner nullptr
    if (value.empty()) {
        return nullptr;
    }

    // Créer un nouvel opérande
    Operand* operand = new Operand;

    // Si la valeur est alphabétique, c’est un registre
    if (std::isalpha(value[0])) {
        operand->type = REGISTER;

        // Traduire le nom du registre en son index
        operand->parsed = registers_id[value];
    } 
    
    // Sinon, c’est une valeur numérique
    else {
        operand->type = NUMERIC;

        // Convertir la chaîne en entier non signé
        operand->parsed = static_cast<uint16_t>(std::stoi(value));
    }

    // Retourner le pointeur vers l’opérande
    return operand;
}


//// Constructeur de la classe Instruction à partir d'une ligne brute
Instruction::Instruction(const std::string& raw)
    : opcode(parse_opcode(parse_line(raw))), operands{nullptr, nullptr} {

    // Dictionnaire associant le nom des registres à leur index
    std::map<std::string, int> registers_id = {
        {"a", 0},
        {"b", 1},
        {"c", 2},
        {"d", 3}
    };

    // Analyse et stockage du premier opérande (s’il existe)
    operands[0] = parse_operand(parse_line(raw), 1, registers_id);

    // Analyse et stockage du second opérande (s’il existe)
    operands[1] = parse_operand(parse_line(raw), 2, registers_id);
}
