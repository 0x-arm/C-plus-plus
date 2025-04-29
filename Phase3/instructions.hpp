#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <string>
#include "operand.hpp"
#include "opcode.hpp"

struct Instruction {
    const Opcode opcode;
    const Operand* operands[2];
    Instruction(const std::string& raw);
    inline ~Instruction();
};

#endif