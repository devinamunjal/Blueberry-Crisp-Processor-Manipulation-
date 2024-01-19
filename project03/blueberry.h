/* (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

/* DO NOT MODIFY THIS FILE OR YOUR CODE WILL NOT COMPILE ON THE SUBMIT
 * SERVER. */

#define NUM_BYTES (16 * 1024)
#define BYTES_PER_WORD 4
#define NUM_WORDS (NUM_BYTES / BYTES_PER_WORD)
enum register_name {R0, R1, R2, R3, R4, R5, R6, R7, R8, R9,
                    R10, R11};
enum opcode {ADD, SUB, MULT, DIV, ADDF, SUBF, MULTF, DIVF, REM, SHL, SHR,
             AND, OR, XOR, NOT, EQ, NE, LT, GT, LE, GE, ITOF, FTOI,
             READI, PRINTI, READF, PRINTF, LW, SW, LI, MOVE, JUMP, HALT};

unsigned short print_instruction(unsigned int instr);
unsigned short disassemble(const unsigned int memory[],
                           unsigned short start_addr,
                           unsigned short pgm_size);
unsigned short encode_instruction(unsigned short opcode, unsigned short reg1,
                                  unsigned short reg2, unsigned short reg3,
                                  unsigned int addr_or_imm,
                                  unsigned int *const instr);
unsigned short relocate(unsigned int memory[], unsigned short start_addr,
                        unsigned short pgm_size, short offset,
                        unsigned short *const num_instrs);
