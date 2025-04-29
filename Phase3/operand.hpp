#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <cstdint>

enum OperandType {
    NUMERIC,
    REGISTER
};

struct Operand {
    OperandType type;
    uint16_t parsed;
};

#endif