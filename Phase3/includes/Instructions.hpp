#pragma once
#include "Operand.hpp"
#include "Opcode.hpp"
#include "Register.hpp"

#include <string>

struct Instruction {
    const Opcode opcode;
    const Operand* operands[2];

    // Constructeur
    Instruction(const std::string& raw);

    // Destructeur
    inline ~Instruction() { delete operands[0]; delete operands[1]; };
};