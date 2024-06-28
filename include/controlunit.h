#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <stdint.h>
#include <types.h>

typedef struct ControlUnit ControlUnit;

struct ControlUnit {
    ctrl reg_write;
    ctrl alu_src;
    ctrl mem_read;
    ctrl mem_write;
    ctrl mem_to_reg;
    ctrl alu_op;
    ctrl branch;
};

int32_t ctrl_imm_gen(uint32_t instr);
void ctrl_unit(ControlUnit *ctrlunit, uint32_t instr);

#endif