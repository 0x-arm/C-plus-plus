#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <string>

enum Opcode { 
    SETv, 
    SETr, 
    ADDv, 
    ADDr, 
    SUBv, 
    SUBr 
};

enum OperandType {
    NUMERIC,
    REGISTER
};

struct Operand {
    OperandType type;
    uint16_t parsed;
};

struct Instruction {
    const Opcode opcode;
    const Operand* operands[2];
    Instruction(const std::string& raw);
    inline ~Instruction();
};

#endif