#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>

constexpr int MAX_MEMORY = 256; // Taille de la mémoire
constexpr int MAX_STACK = 16; // Taille de la pile
constexpr int OCTET_SIZE = 8; // Taille d'un octet (8 bits)

// Classe Memory
class Memory {
private:
    uint8_t _memory[256];
    uint8_t _SP = 0;

public:
    Memory();

    uint16_t read(uint8_t address);
    void write(uint8_t address, uint16_t value);
    void push(uint16_t value);
    uint16_t pop();
};

#endif