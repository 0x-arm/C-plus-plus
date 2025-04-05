// memory.cpp

#include <iostream> // Pour std::cout
#include <cstdlib> // Pour std::exit
#include "memory.hpp"

// Taille totale de la mémoire : 2^8 = 256 octets
uint8_t memory[256];

// Pointeur de pile (Stack Pointer) initialisé à 0
uint8_t SP = 0;

// Fonction de lecture (read) : lit 2 octets consécutifs (16 bits) en little endian
uint16_t read(uint8_t address) {
    return memory[address] | (memory[address + 1] << 8);
}

// Fonction d’écriture (write) : écrit 2 octets consécutifs (16 bits) en little endian
void write(uint8_t address, uint16_t value) {
    memory[address] = value & 0xFF;           // Octet de poids faible
    memory[address + 1] = (value >> 8);
    
    std::cout << memory[address] << " " << (memory[address + 1] << 8) << std::endl;  // Octet de poids fort
}

// Ajoute une valeur 16 bits au sommet de la pile
void push(uint16_t value) {
    
    // Vérifie si la pile déborde (au-delà de l’adresse 15)
    if (SP + 1 >= 16) {
        std::exit(1);
    }

    memory[SP] = value & 0xFF;                // Octet de poids faible
    memory[SP + 1] = (value >> 8);            // Octet de poids fort
    SP += 2;
}

// Retire une valeur 16 bits du sommet de la pile et la retourne
uint16_t pop() {
    // Vérifie si la pile est vide
    if (SP < 2) {
        std::exit(1); 
    }

    SP -= 2;
    return memory[SP] | (memory[SP + 1] << 8);
}
