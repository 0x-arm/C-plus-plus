#include "Memory.hpp"
#include <cstdlib>

// Constructeur : initialise la mémoire et le pointeur de pile
Memory::Memory() {
    for (int i = 0; i < 256; ++i) {
        _memory[i] = 0;
    }
}

uint16_t Memory::read(uint8_t address) {
    return _memory[address] | (_memory[address + 1] << 8);
}

void Memory::write(uint8_t address, uint16_t value) {
    _memory[address] = value & 0xFF;
    _memory[address + 1] = value >> 8;
}

void Memory::push(uint16_t value) {
    if (_SP + 1 >= 16) std::exit(1);
    _memory[_SP] = value & 0xFF;
    _memory[_SP + 1] = value >> 8;
    _SP += 2;
}

uint16_t Memory::pop() {
    if (_SP < 2) std::exit(1);
    _SP -= 2;
    return _memory[_SP] | (_memory[_SP + 1] << 8);
}