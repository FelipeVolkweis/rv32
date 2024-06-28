#ifndef ALU_H
#define ALU_H

#include <stdint.h>

typedef struct ALU ALU;

struct ALU {
    int32_t in_a;
    int32_t in_b;
    int32_t out_result;
    uint32_t out_zero;
};

void alu_add(ALU *alu);
void alu_sub(ALU *alu);
void alu_and(ALU *alu);
void alu_or(ALU *alu);
void alu_sll(ALU *alu);
void alu_srl(ALU *alu);


#endif // ALU_H