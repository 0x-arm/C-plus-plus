#pragma once

#include <cstdint>

class Memory {

private:
        uint8_t* MEM;
        uint8_t _SP;

public:

    // Constructeur de la mémoire
    inline Memory(uint8_t nbits) {
        MEM = new uint8_t[1 << nbits];
        _SP = 0;
    };

    // Libération de la mémoire allouée
    inline ~Memory() {
        delete[] MEM;
    };

    // TODO surcharge de l'opérateur []
    uint16_t& operator[](uint16_t address);

    uint16_t pop();
    void push(uint16_t value);
};