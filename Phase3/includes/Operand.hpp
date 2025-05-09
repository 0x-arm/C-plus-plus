#pragma once
#include "OperandType.hpp"

#include <cstdint>

struct Operand {
    OperandType type;
    uint16_t parsed;
};