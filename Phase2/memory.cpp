#include <iostream>
#include <cstdlib>
#include "Memory.hpp"

// Constructeur : initialise la mémoire et le pointeur de pile
Memory::Memory() {
    for (int i = 0; i < 256; ++i) {
        _memory[i] = 0;
    }
}

//// Méthode de lecture (read) : lit 2 octets consécutifs (16 bits) en little endian
uint16_t Memory::read(uint8_t address) {
    
    // Taille de la mémoire
    constexpr int MAX_MEMORY = 256;

    // Récupération de la valeur saturée à l'adresse mémoire spécifiée (octet de poids faible + octet de poids fort)
    uint16_t value = std::min(std::max((_memory[address] | (_memory[address + 1] << 8)), 0), MAX_MEMORY);

    // Retourner la valeur lue saturée
    return value; // seulement memory[address] | (memory[address + 1] << 8) ==> 33304 car non borné/saturée
}

//// Méthode d’écriture (write) : écrit 2 octets consécutifs (16 bits) en little endian
void Memory::write(uint8_t address, uint16_t value) {

    // Octet de poids faible
    _memory[address] = value & 0xFF;

    // Octet de poids fort
    _memory[address + 1] = (value >> 8);
}

//// Méthode qui ajoute une valeur 16 bits au sommet de la pile
void Memory::push(uint16_t value) {
    
    // Vérifier si la pile déborde (au-delà de l’adresse 15)
    if (_SP + 1 >= 16) {

        // Quitter le programme
        std::exit(1);
    }

    // Récupérer l'octet de poids faible
    _memory[_SP] = value & 0xFF;

    // Récupérer l'octet de poids fort
    _memory[_SP + 1] = (value >> 8);

    // Incrémenter le pointeur de pile
    _SP += 2;
}

//// Méthode qui retire une valeur 16 bits du sommet de la pile et la retourne 
uint16_t Memory::pop() {

    // Vérifier si la pile est vide
    if (_SP < 2) {

        // Quitter le programme
        std::exit(1); 
    }

    // Décrémenter le pointeur de pile
    _SP -= 2;

    // Retourner la valeur lue de la pile (octet de poids faible + octet de poids fort)
    return _memory[_SP] | (_memory[_SP + 1] << 8);

}