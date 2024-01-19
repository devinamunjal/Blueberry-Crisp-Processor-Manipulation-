/*dmunjal
119016480
section: 0201
I pledge on my honor that I have not given or
received any assistance on this project 
this project has four method, print instructions, dissemble,
relocate and encode instructions that basically all deal with
32 bit words invovling extracting and bitwising shifting to 
both encode and decode the instrucitons. also, relocate deals
with moving instructions to diff parts of memory
*/

#include "blueberry.h"
#include <stdio.h>
/*helper method that takes in decimal
  value and returns the corersponding opcode val */
const char* opcode(int o){
  if(o == 0){
    return "add";
  }
  else if(o == 1){
    return "sub";
  }
  else if(o == 2){
    return "mult";
  }
  else if(o == 3){
    return "div";
  }
  else if(o == 4){
    return "addf";
  }
  else if(o == 5){
    return "subf";
  }
  else if(o == 6){
    return "multf";
  }
  else if(o == 7){
   return "divf";
  }
  else if(o == 8){
   return "rem";
  }
  else if(o == 9){
    return "shl";
  }
  else if(o == 10){
    return "shr";
  }
  else if(o == 11){
    return "and";
  }
  else if(o == 12){
    return "or";
  }
  else if(o == 13){
    return "xor";
  }
  else if(o == 14){
    return "not";
  }
  else if(o == 15){
    return "eq";
  }
  else if(o == 16){
    return "ne";
  }
  else if(o == 17){
    return "lt";
  }
  else if(o == 18){
    return "gt";
  }
  else if(o == 19){
    return "le";
  }
  else if(o == 20){
    return "ge";
  }
  else if(o == 21){
    return "itof";
  }
  else if(o == 22){
    return "ftoi";
  }
  else if(o == 23){
    return "readi";
  }
  else if(o == 24){
    return "printi";
  }
  else if(o == 25){
    return "readf";
  }
  else if(o == 26){
    return "printf";
  }
  else if(o == 27){
    return "lw";
  }
  else if(o == 28){
    return "sw";
  }
  else if(o == 29){
    return "li";
  }
  else if(o == 30){
    return "move";
  }
  else if(o == 31){
    return "jump";
  }
  else if(o == 32){
    return "halt";
  }
  else{
    return NULL;
  }
}
/*decodes the 32 bits seperating and extracting each part, opcode, reg 1-3, and addr/imm */
unsigned short print_instruction(unsigned int instr){
  unsigned int *i = &instr; /* pointer to instr */
  unsigned int value = ( *i >> 26) & 0x3F; /*extracts opcode */
  const char *o = opcode(value); /*actual opcode character */
  const char *target = "li";
  unsigned int r1 = (*i >> 22) & 0xF;
  unsigned int r2= (*i >> 18) & 0xF;
  unsigned int r3 = (*i >> 14) & 0xF;
  unsigned int memory = *i & 0x3FFFF;
  
  if((r1 < 0 || r1 > 11) || (r2 < 0 || r2 > 11) || (r3 < 0 || r3 > 11)){
    return 0;
  }
  if(memory % 4 != 0 && o != target ){
    return 0;
  }
  if(value < 33){
    printf("%s\t", o);
  }
  else{
    return 0;
  }
  if(r1 == 0 || r1 == 11){
    return 0;
  }
  if(value  >= 0 && value <= 13) {
    printf("R%d R%d R%d ", r1,r2, r3);
  }
  if(value >= 15 && value <= 20) {
    printf("R%d R%d R%d ", r1 ,r2, r3);
  }
  if(value == 14 || value  == 21 || value == 22 || value  == 30){
    printf("R%d R%d ",r1,r2);
  }
  if((value  >= 23 && value  <= 29) || value == 31){
    printf("R%d ",r1);
  }
  if((value  >= 27 && value <= 29) || value == 31){
    if(o != target)
      printf("%05d", memory);
    else{
      printf("%d", memory);
    }
  }
  printf("\n");
  return 1;
  
}
/* this method takes in the memory arr and start address and calls the print instruction
   method on each instruction in the array */
unsigned short disassemble(const unsigned int memory[],
                           unsigned short start_addr,
                           unsigned short pgm_size){
  int max_word_address = 4096;
  unsigned int start_subscript = start_addr / 4;
  int i;
  if(start_addr > max_word_address || pgm_size > 32 || start_addr > NUM_WORDS ){
    return 0;
  }
  if(pgm_size == 0){
    return 1;
  }
  if(start_subscript  + pgm_size > NUM_WORDS){
    return 0;
  }
  if(start_addr % 4 != 0){
    return 0;
  }
  /*iterate through the loop and prints the instruction unless its 0 */
  for(i = start_subscript; i < start_subscript + pgm_size; i++){
    if(print_instruction(memory[i]) == 0){
      return 0;
    }
  }
  return 1;
}
/*checks if the registers are in range based on the opcode to see which ones are used */
unsigned int check_register(int o, unsigned short  reg1, unsigned short reg2, unsigned short reg3){
  if (o >= 0 && o <= 13) {
    if (reg1 < 0 || reg1 > 11 || reg2 < 0 || reg2 > 11 || reg3 < 0 || reg3 > 11) {
      return 0;
    }
  }
  if (o >= 15 && o <= 20) {
    if (reg1 < 0 || reg1 > 11 || reg2 < 0 || reg2 > 11 || reg3 < 0 || reg3 > 11) {
      return 0;
    }
  }
  if ((o == 14 || o == 21 || o == 22 || o == 30)) {
     if (reg1 < 0 || reg1 > 11 || reg2 < 0 || reg2 > 11) {
       return 0;
     }
  }
  if (o >= 23 && (o <= 29 || o == 31)) {
     if (reg1 < 0 || reg1 > 11) {
       return 0;
     }
  }
  return 1;

}
/*encode instr uses all of the parameters (opcode, reg1,reg2, reg3, addr/imm) to 
  put together(encode) all 32 bits */
unsigned short encode_instruction(unsigned short opcode, unsigned short reg1,
                                  unsigned short reg2, unsigned short reg3,
                                  unsigned int addr_or_imm,
                                  unsigned int *const instr){
  /* declares variables */
  unsigned int encode_instr = 0;

  /*checks if instr is null */
  if(instr == NULL){
    return 0;
  }

  /*checks to see if opcode is in range */
  if(opcode < 0 || opcode > 32){
    return 0;
  }

  /*checks to see if registers are in range */
  if(check_register(opcode, reg1, reg2, reg3) == 0){
    return 0;
  }

  /*checks to seee if registers are 0 -11 */
  if(reg1 < 0 || reg1 > 11 || reg2 < 0 || reg2 > 11 || reg3 < 0 || reg3 > 11){
    return 0;
  }
  /*checks size of addr/imm */
  if (addr_or_imm < 0 || addr_or_imm >= 16384){
    return 0;
  }
  /*uses bitwise operators to encode the instr */
  encode_instr |= (opcode << 26); /*first 6 bits */
  encode_instr |= (reg1 << 22); /* 6-10 bits */
  encode_instr |= (reg2 << 18); /* 10-14 bits */
  encode_instr |= (reg3 << 14); /* 14-18 bits */
  
  /* checks to see if opcode uses addr/imm */
  if(opcode == 27 || opcode == 28 || opcode == 29 || opcode == 31){
    if(addr_or_imm % 4 == 0){
      /*last 14 bits */
      encode_instr |= addr_or_imm;
 
    }
  }
  /*sets instr pointer to encode instr */
  *instr = encode_instr;
  return 1;
}
/*moves a a part of program from one part of memory to another based on
  the memory arr, start_addr, pgm_size, offset, and *num_instrs 
  while also counting the num of instructions*/
unsigned short relocate(unsigned int memory[], unsigned short start_addr,
                        unsigned short pgm_size, short offset,
                        unsigned short *const num_instrs){
  /*declare variables*/
  int i; /*counter for for loop */
  unsigned short opcode = 0; 
  unsigned short reg1 = 0;
  unsigned short reg2 = 0;
  unsigned short reg3 = 0;
  unsigned int addr_or_imm = 0;
  unsigned int start_subscript = 0;
  
/* if any of these checks are valid returns 0 */
  /* check if the size is > than # of words */
  if(pgm_size > NUM_WORDS){
    return 0;
  }
  
  /*checks if # of instr is null n if not intializes */
  if(num_instrs == NULL){
    return 0;
  }
  *num_instrs = 0;
  /*checks if offset or pgm_size is 0 */
  if(offset == 0 || pgm_size == 0){
    return 0;
  }
  
  /*checks if start_addr is divisble by 4 n the size 
  if(start_addr % 4 != 0 )){
    return 0;
    } */

  /*checks the size of current stat addr */
  if(start_addr >= NUM_WORDS || start_addr < 0){
    return 0;
  }
  start_subscript = start_addr /4;
  if(pgm_size + start_subscript + offset > 32
     || pgm_size + start_subscript + offset < 0){
    return 0;
  }

  /* iterates through the memory arr */
  for(i = start_subscript; i <  pgm_size + start_subscript; i++){
    memory[i + offset] = memory[i];
    /*masks n shifts the opcode */
    opcode = (memory[i] >> 26) & 0x3F;

    /*masks n shifts first reg. */
    reg1  = (memory[i] >> 22) & 0xF;

    /*masks n shifts second reg. */
    reg2 = (memory[i] >> 18) & 0xF;

    /*masks n shifts third reg. */
    reg3 = (memory[i] >> 14) & 0xF;

    /*masks n shifts addr/imm */
    addr_or_imm = memory[i] & 0x3FFF;
    
    /*if any hold true then it returns 0 */
    /*checks if first reg is 0 or 11 */
    if(reg1 == 0 || reg1 == 11){
      return 0;
    }

    /*checks if the registers are out of range */
    if(check_register(opcode, reg1, reg2, reg3) == 0){
      return 0;
    }
    /*checks to see if opcode is in range */
    if(opcode < 0 || opcode > 32){
      return 0;
    }

    /*checks to see if opcode uses addr/imm */
    if (opcode == 27 || opcode == 28 || opcode == 31){
      /*checks to see if addr/imm is divisible by 4 n the size */
      if(addr_or_imm % 4 == 0){
	(*num_instrs)++;
      }
      else{
	return 0;
     }
    
   }
  

  }
  return 1;

}
