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

void alu_ctrl_unit(ALU *alu, ControlUnit *ctrl, uint8_t funct3, uint8_t funct7) {
    switch (ctrl->alu_op) {
        case 0:
            alu->ctrl_line = OP_ADD;
            break;
        case 1:
            alu->ctrl_line = OP_SUB;
            break;
        case 2:
            if (funct3 == 0b000 && funct7 == 0b0000000) {
                alu->ctrl_line = OP_ADD;
            } else if (funct3 == 0b000 && funct7 == 0b0100000) {
                alu->ctrl_line = OP_SUB;
            } else if (funct3 == 0b110 && funct7 == 0b0000000) {
                alu->ctrl_line = OP_OR;
            } else if (funct3 == 0b111 && funct7 == 0b0000000) {
                alu->ctrl_line = OP_AND;
            }

            break;
    }
}

void alu_exec(ALU *alu) {
    switch (alu->ctrl_line) {
        case OP_ADD:
            alu_add(alu);
            break;
        case OP_SUB:
            alu_sub(alu);
            break;
        case OP_AND:
            alu_and(alu);
            break;
        case OP_OR:
            alu_or(alu);
            break;
    }
}