#include <iostream>
#include <cstdlib>
#include "Memory.hpp"

// Taille de la mémoire
constexpr int MAX_MEMORY = 256;

// Taille de la pile
constexpr int MAX_STACK = 16;

// Taille d'un octet (8 bits)
constexpr int OCTES_SIZE = 8;

// Constructeur : initialise la mémoire et le pointeur de pile
Memory::Memory() {
    for (int i = 0; i < MAX_MEMORY; ++i) {
        _memory[i] = 0;
    }
}

//// Méthode qui lit une valeur sur 16 bits dans la mémoire en little endian
uint16_t Memory::read(uint8_t address) {

    // Récupération de la valeur saturée à l'adresse mémoire spécifiée (octet de poids faible + octet de poids fort)
    uint16_t value = std::min(std::max((_memory[address] | (_memory[address + 1] << OCTES_SIZE)), 0), MAX_MEMORY);

    // Retourner la valeur lue saturée
    return value; // seulement memory[address] | (memory[address + 1] << 8) ==> résultat = 33304 car value = non borné/saturée
}

//// Méthode qui écrit une valeur sur 16 bits dans la mémoire en little endian
void Memory::write(uint8_t address, uint16_t value) {

    // // Récupérer l'octet de poids faible
    _memory[address] = static_cast<uint8_t>(value);

    // Récupérer l'octet de poids fort
    _memory[address + 1] = static_cast<uint8_t>(value >> OCTES_SIZE);

}

//// Méthode qui ajoute une valeur 16 bits au sommet de la pile
void Memory::push(uint16_t value) {
    
    // Vérifier si la pile déborde (au-delà de l’adresse 15)
    if (_SP + 1 >= MAX_STACK) {

        // Quitter le programme
        std::exit(1);
    }

    // Récupérer l'octet de poids faible
    _memory[_SP] = static_cast<uint8_t>(value);

    // Récupérer l'octet de poids fort
    _memory[_SP + 1] = static_cast<uint8_t>(value >> OCTES_SIZE);

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
    return _memory[_SP] | (_memory[_SP + 1] << OCTES_SIZE);

}