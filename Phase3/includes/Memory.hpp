#pragma once

#include <cstdint>

class Memory {

private:
        uint8_t* MEM;
        uint8_t SP;
        uint32_t SIZE;

public:

    // Constructeur de la mémoire
    inline Memory(uint8_t nbits) {

        // Calcul de la taille de la mémoire à allouer en fonction du nombre de bits (1 << nbits = 2^nbits)
        SIZE = 1 << nbits;

        // Allocation dynamique d'un tableau de uint8_t de taille 'size'
        MEM = new uint8_t[SIZE];

        // Initialiser le pointeur à 0
        SP = 0;
    };

    // Destructeur de la mémoire
    inline ~Memory() {
        
        // Libération de la mémoire allouée pour le tableau MEM
        delete[] MEM;
    };

    // TODO surcharge de l'opérateur []
    uint16_t& operator[](uint16_t address);

    uint16_t pop();
    void push(uint16_t value);
};