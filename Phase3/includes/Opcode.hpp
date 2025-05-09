#pragma once

enum Opcode {
    SETv, 
    SETr, 
    ADDv,
    ADDr, 
    SUBv, 
    SUBr,
    IFNZ,
    PRINT,
    STORE,
    LOAD,
    PUSH,
    POP
};