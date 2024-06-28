#include <alu.h>

void alu_add(ALU *alu) {
    alu->out_result = alu->in_a + alu->in_b;
    alu->out_zero = alu->out_result == 0;
}

void alu_sub(ALU *alu) {
    alu->out_result = alu->in_a - alu->in_b;
    alu->out_zero = alu->out_result == 0;
}

void alu_and(ALU *alu) {
    alu->out_result = alu->in_a & alu->in_b;
    alu->out_zero = alu->out_result == 0;
}

void alu_or(ALU *alu) {
    alu->out_result = alu->in_a | alu->in_b;
    alu->out_zero = alu->out_result == 0;
}

void alu_sll(ALU *alu) {
    alu->out_result = alu->in_a << alu->in_b;
    alu->out_zero = alu->out_result == 0;
}

void alu_srl(ALU *alu) {
    alu->out_result = alu->in_a >> alu->in_b;
    alu->out_zero = alu->out_result == 0;
}