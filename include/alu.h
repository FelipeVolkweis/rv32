#ifndef ALU_H
#define ALU_H

#include <controlunit.h>

#include <stdint.h>

#define OP_ADD 0b0010
#define OP_SUB 0b0110
#define OP_AND 0b0000
#define OP_OR  0b0001

typedef struct ALU ALU;

struct ALU {
    int32_t in_a;
    int32_t in_b;
    int32_t out_result;
    uint32_t out_zero;

    uint8_t ctrl_line;
};

void alu_add(ALU *alu);
void alu_sub(ALU *alu);
void alu_and(ALU *alu);
void alu_or(ALU *alu);
void alu_sll(ALU *alu);
void alu_srl(ALU *alu);

void alu_ctrl_unit(ALU *alu, ControlUnit *ctrl, uint8_t funct3, uint8_t funct7);
void alu_exec(ALU *alu);


#endif // ALU_H