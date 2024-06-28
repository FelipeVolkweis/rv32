#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

typedef struct Registers Registers;

struct Registers {
    uint32_t reg[32];
    uint32_t rs1;
    uint32_t rs2;
    uint32_t rd;
};

#endif // REGISTERS_H