#include <datapath.h>
#include <opcodes.h>

void fetch(InstructionMemory *imem, DataMemory *dmem) {
    imem_read(imem, dmem);
    imem->pc.pc4 = imem->pc.value + 4;
}

void decode(InstructionMemory *imem, Registers *regs, ControlUnit *ctrlunit) {
    ctrl_unit(ctrlunit, imem->ir);

    uint8_t opcode = imem->ir >> 26 & OPCODE_MASK;
    uint8_t func3 = imem->ir >> 12 & FUNCT3_MASK;
    uint8_t func7 = imem->ir >> 25 & FUNCT7_MASK;

    regs->rd = imem->ir >> 7 & RD_MASK;
    regs->rs1 = imem->ir >> 15 & RS1_MASK;
    regs->rs2 = imem->ir >> 20 & RS2_MASK;
}

void execute(InstructionMemory *imem, Registers *regs, ALU *alu, ControlUnit *ctrlunit) {
    int32_t imm = ctrl_imm_gen(imem->ir);
    int32_t branch_target = imem->pc.value + (imm << 1);

    alu->in_a = regs->reg[regs->rs1];
    alu->in_b = ctrlunit->alu_src == 0 ? regs->reg[regs->rs2] : imm;
}

void memory(InstructionMemory *imem, Registers *regs, DataMemory *dmem, ALU *alu, ControlUnit *ctrlunit) {
    if (ctrlunit->mem_read) {

    } else if (ctrlunit->mem_write) {

    }

    if (ctrlunit->branch && alu->out_zero) {
        imem->pc.value = imem->pc.branch_target;
    } else {
        imem->pc.value = imem->pc.pc4;
    }
}

void writeback(Registers *regs, ALU *alu, ControlUnit *ctrlunit) {
    if (ctrlunit->reg_write) {
    }
}