#ifndef DATAPATH_H
#define DATAPATH_H

#include <registers.h>
#include <controlunit.h>
#include <alu.h>
#include <instructionmemory.h>
#include <datamemory.h>

void fetch(InstructionMemory *imem, DataMemory *dmem);
void decode(InstructionMemory *imem, Registers *regs, ControlUnit *ctrlunit);
void execute(InstructionMemory *imem, Registers *regs, ALU *alu, ControlUnit *ctrlunit);
void memory(InstructionMemory *imem, Registers *regs, DataMemory *dmem, ALU *alu, ControlUnit *ctrlunit);
void writeback(Registers *regs, ALU *alu, ControlUnit *ctrlunit, DataMemory *dmem);

#endif // DATAPATH_H