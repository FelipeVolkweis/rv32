#include <controlunit.h>
#include <opcodes.h>
#include <stdint.h>

// Masks and shifts for extracting immediate fields
#define I_IMM_MASK 0xFFF
#define I_IMM_SHIFT 20

#define S_IMM_MASK_HIGH 0xFE000000
#define S_IMM_MASK_LOW 0xF80
#define S_IMM_SHIFT_HIGH 25
#define S_IMM_SHIFT_LOW 7

#define B_IMM_MASK_HIGH 0x80000000
#define B_IMM_MASK_MID 0x7E000000
#define B_IMM_MASK_LOW 0xF00
#define B_IMM_MASK_LOWEST 0x80
#define B_IMM_SHIFT_HIGH 31
#define B_IMM_SHIFT_MID 25
#define B_IMM_SHIFT_LOW 8
#define B_IMM_SHIFT_LOWEST 7

#define J_IMM_MASK_HIGH 0x80000000
#define J_IMM_MASK_MID 0xFF000
#define J_IMM_MASK_LOW 0x100000
#define J_IMM_MASK_LOWEST 0x7FE00000
#define J_IMM_SHIFT_HIGH 31
#define J_IMM_SHIFT_MID 12
#define J_IMM_SHIFT_LOW 20
#define J_IMM_SHIFT_LOWEST 21

#define U_IMM_MASK 0xFFFFF000

// Function to sign-extend a 12-bit immediate to 32-bit
int32_t sign_extend_12(uint32_t imm) {
    return (imm & 0x800) ? (imm | 0xFFFFF000) : imm;
}

// Function to sign-extend a 13-bit immediate to 32-bit
int32_t sign_extend_13(uint32_t imm) {
    return (imm & 0x1000) ? (imm | 0xFFFFE000) : imm;
}

// Function to sign-extend a 21-bit immediate to 32-bit
int32_t sign_extend_21(uint32_t imm) {
    return (imm & 0x100000) ? (imm | 0xFFE00000) : imm;
}

// Function to sign-extend a 32-bit immediate to 32-bit (trivial)
int32_t sign_extend_32(uint32_t imm) {
    return (int32_t)imm;
}

int32_t ctrl_imm_gen(uint32_t instr) {
    uint8_t opcode = (instr >> 26) & OPCODE_MASK;
    uint32_t imm = 0;

    switch (opcode) {
    case I_TYPE: // imm[11:0]
        imm = (instr >> I_IMM_SHIFT) & I_IMM_MASK;
        return sign_extend_12(imm);

    case S_TYPE: // imm[11:5] | rs2 | rs1 | funct3 | imm[4:0]
        imm = ((instr & S_IMM_MASK_HIGH) >> (S_IMM_SHIFT_HIGH - 5)) | ((instr >> S_IMM_SHIFT_LOW) & 0x1F);
        return sign_extend_12(imm);

    case B_TYPE: // imm[12] | imm[10:5] | rs2 | rs1 | funct3 | imm[4:1] | imm[11]
        imm = ((instr & B_IMM_MASK_HIGH) >> (B_IMM_SHIFT_HIGH - 12)) |
              ((instr & B_IMM_MASK_MID) >> (B_IMM_SHIFT_MID - 5)) |
              ((instr & B_IMM_MASK_LOW) >> (B_IMM_SHIFT_LOW - 1)) |
              ((instr & B_IMM_MASK_LOWEST) << 4);
        return sign_extend_13(imm);

    case JAL: // imm[20] | imm[10:1] | imm[11] | imm[19:12]
        imm = ((instr & J_IMM_MASK_HIGH) >> (J_IMM_SHIFT_HIGH - 20)) |
              ((instr & J_IMM_MASK_MID)) |
              ((instr & J_IMM_MASK_LOW) >> (J_IMM_SHIFT_LOW - 11)) |
              ((instr & J_IMM_MASK_LOWEST) >> (J_IMM_SHIFT_LOWEST - 1));
        return sign_extend_21(imm);

    case JALR:
        imm = (instr >> I_IMM_SHIFT) & I_IMM_MASK;
        return sign_extend_12(imm);

    case LUI: // imm[31:12]
    case AUIPC:
        imm = instr & U_IMM_MASK;
        return sign_extend_32(imm);

    default:
        return 0;
    }
}


void ctrl_unit(ControlUnit *ctrlunit, uint32_t instr) {
    // Extract the opcode from the instruction
    uint8_t opcode = (instr >> 26) & OPCODE_MASK;

    // Reset all control signals
    ctrlunit->reg_write = 0;
    ctrlunit->alu_src = 0;
    ctrlunit->mem_read = 0;
    ctrlunit->mem_write = 0;
    ctrlunit->mem_to_reg = 0;
    ctrlunit->alu_op = 0;
    ctrlunit->branch = 0;

    // Set control signals based on the opcode
    switch (opcode) {
        case R_TYPE: // R-type instructions
            ctrlunit->reg_write = 1;
            ctrlunit->alu_src = 0;
            ctrlunit->mem_read = 0;
            ctrlunit->mem_write = 0;
            ctrlunit->mem_to_reg = 0;
            ctrlunit->alu_op = 2; // ALU operation for R-type
            ctrlunit->branch = 0;
            break;

        case I_TYPE: // I-type instructions (load and arithmetic)
            ctrlunit->reg_write = 1;
            ctrlunit->alu_src = 1;
            ctrlunit->mem_read = 0;
            ctrlunit->mem_write = 0;
            ctrlunit->mem_to_reg = 0;
            ctrlunit->alu_op = 0; // ALU operation for I-type
            ctrlunit->branch = 0;
            break;

        case LOAD: // Load instructions
            ctrlunit->reg_write = 1;
            ctrlunit->alu_src = 1;
            ctrlunit->mem_read = 1;
            ctrlunit->mem_write = 0;
            ctrlunit->mem_to_reg = 1;
            ctrlunit->alu_op = 0; // ALU operation for load
            ctrlunit->branch = 0;
            break;

        case S_TYPE: // S-type instructions (store)
            ctrlunit->reg_write = 0;
            ctrlunit->alu_src = 1;
            ctrlunit->mem_read = 0;
            ctrlunit->mem_write = 1;
            ctrlunit->mem_to_reg = 0;
            ctrlunit->alu_op = 0; // ALU operation for store
            ctrlunit->branch = 0;
            break;

        case B_TYPE: // B-type instructions (branch)
            ctrlunit->reg_write = 0;
            ctrlunit->alu_src = 0;
            ctrlunit->mem_read = 0;
            ctrlunit->mem_write = 0;
            ctrlunit->mem_to_reg = 0;
            ctrlunit->alu_op = 1; // ALU operation for branch
            ctrlunit->branch = 1;
            break;

        case JAL: // J-type instructions (JAL)
            ctrlunit->reg_write = 1;
            ctrlunit->alu_src = 0;
            ctrlunit->mem_read = 0;
            ctrlunit->mem_write = 0;
            ctrlunit->mem_to_reg = 0;
            ctrlunit->alu_op = 0; // ALU operation for JAL
            ctrlunit->branch = 1;
            break;

        case JALR: // J-type instructions (JALR)
            ctrlunit->reg_write = 1;
            ctrlunit->alu_src = 1;
            ctrlunit->mem_read = 0;
            ctrlunit->mem_write = 0;
            ctrlunit->mem_to_reg = 0;
            ctrlunit->alu_op = 0; // ALU operation for JALR
            ctrlunit->branch = 1;
            break;

        case LUI: // U-type instructions (LUI)
        case AUIPC: // U-type instructions (AUIPC)
            ctrlunit->reg_write = 1;
            ctrlunit->alu_src = 1;
            ctrlunit->mem_read = 0;
            ctrlunit->mem_write = 0;
            ctrlunit->mem_to_reg = 0;
            ctrlunit->alu_op = 3; // ALU operation for LUI and AUIPC
            ctrlunit->branch = 0;
            break;

        default:
            // Handle unknown opcode
            break;
    }
}