#ifndef INSTRUCTIONMEMORY_H
#define INSTRUCTIONMEMORY_H

#include <datamemory.h>

#include <stdint.h>

typedef struct InstructionMemory InstructionMemory;
typedef struct PC PC;

struct PC {
    uint32_t value;
    uint32_t pc4;
    uint32_t branch_target;
};

struct InstructionMemory {
    uint32_t ir;
    PC pc;
};

uint32_t imem_read(InstructionMemory *imem, DataMemory *dmem);

#endif // INSTRUCTIONMEMORY_H