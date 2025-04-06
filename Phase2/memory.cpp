#include <iostream> // Pour std::cout
#include <cstdlib> // Pour std::exit
#include "memory.hpp"

// Taille totale de la mémoire : 2^8 = 256 octets
uint8_t memory[256];

// Pointeur de pile (Stack Pointer) initialisé à 0
uint8_t SP = 0;

//// Fonction de lecture (read) : lit 2 octets consécutifs (16 bits) en little endian
uint16_t read(uint8_t address) {
    
    // Taille de la mémoire
    constexpr int MAX_MEMORY = 256;

    // Retourner la valeur lue saturée à l'adresse mémoire spécifiée (octet de poids faible + octet de poids fort)
    return std::min(std::max((memory[address] | (memory[address + 1] << 8)), 0), MAX_MEMORY); // seulement memory[address] | (memory[address + 1] << 8) ==> 33304 car non-borné
}

//// Fonction d’écriture (write) : écrit 2 octets consécutifs (16 bits) en little endian
void write(uint8_t address, uint16_t value) {

    // Octet de poids faible
    memory[address] = value & 0xFF;

    // Octet de poids fort
    memory[address + 1] = (value >> 8);
}

//// Ajoute une valeur 16 bits au sommet de la pile
void push(uint16_t value) {
    
    // Vérifier si la pile déborde (au-delà de l’adresse 15)
    if (SP + 1 >= 16) {

        // Quitter le programme
        std::exit(1);
    }

    // Récupérer l'octet de poids faible
    memory[SP] = value & 0xFF;

    // Récupérer l'octet de poids fort
    memory[SP + 1] = (value >> 8);

    // Incrémenter le pointeur de pile
    SP += 2;
}

//// Retire une valeur 16 bits du sommet de la pile et la retourne 
uint16_t pop() {

    // Vérifier si la pile est vide
    if (SP < 2) {

        // Quitter le programme
        std::exit(1); 
    }

    // Décrémenter le pointeur de pile
    SP -= 2;

    // Retourner la valeur lue de la pile (octet de poids faible + octet de poids fort)
    return memory[SP] | (memory[SP + 1] << 8);
}