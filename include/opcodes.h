#ifndef OPCODES
#define OPCODES

#define OPCODE_MASK 0b01111111
#define RD_MASK 0x1f
#define RS1_MASK 0x1f
#define RS2_MASK 0x1f
#define FUNCT3_MASK 0x7
#define FUNCT7_MASK 0x7f

#define U_TYPE
    #define LUI   0b00110111
    #define AUIPC 0b00010111

#define J_TYPE 
    #define JAL   0b01101111
    #define JALR  0b01100111

#define B_TYPE 0b01100011
    #define BEQ     0x0
    #define BNE     0x1
    #define BLT     0x4
    #define BGE     0x5
    #define BLTU    0x6
    #define BGEU    0x7

#define LOAD    0x03
    #define LB      0x0
    #define LH      0x1
    #define LW      0x2
    #define LD      0x3
    #define LBU     0x4
    #define LHU     0x5
    #define LWU     0x6

#define S_TYPE 0b00100011
    #define SB      0x0
    #define SH      0x1
    #define SW      0x2
    #define SD      0x3

#define I_TYPE 0b00010011
    #define ADDI    0x0
    #define SLLI    0x1
    #define SLTI    0x2
    #define SLTIU   0x3
    #define XORI    0x4
    #define SRI     0x5
        #define SRLI    0x00
        #define SRAI    0x20
    #define ORI     0x6
    #define ANDI    0x7

#define R_TYPE 0b00110011
    #define ADDSUB  0x0
        #define ADD     0x00
        #define SUB     0x20
    #define SLL     0x1
    #define SLT     0x2
    #define SLTU    0x3
    #define XOR     0x4
    #define SR      0x5
        #define SRL     0x00
        #define SRA     0x20
    #define OR      0x6
    #define AND     0x7


#endif // OPCODES