#include <stdio.h>
#include <assert.h>
#include "blueberry.h"

/* CMSC 216, Fall 2023, Project #3
 * Public test 11 (public11.c)
 *
 * Tests calling relocate() with valid parameters, where the program to be
 * relocated doesn't have any instructions that use memory addresses.
 *
 * (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

#define NUM_INSTRUCTIONS 7
#define START_ADDR 0
#define OFFSET 10

int main(void) {
  unsigned int program[NUM_INSTRUCTIONS]= {0x74c000d8, 0x75000084, 0x008d0000,
                                           0x08488000, 0x25668000, 0x369d0000,
                                           0x48854000};
  unsigned int memory[NUM_WORDS]= {0};
  unsigned short count= 0;
  int i;

  /* first copy the program into the memory array, starting at location 0 */
  for (i= 0; i < NUM_INSTRUCTIONS; i++)
    memory[i + START_ADDR]= program[i];

  /* now relocate the program starting at the 10th memory word (10 words
     after where it is initially) */
  relocate(memory, START_ADDR, NUM_INSTRUCTIONS, OFFSET, &count);

  /* check that the program is now located in memory at words 10..16 */
  for (i= 0; i < NUM_INSTRUCTIONS; i++)
    assert(memory[i + START_ADDR + OFFSET] == program[i]);

  /* check that the program is also still located in memory at words 0..6
     where it was before being relocated */
  for (i= 0; i < NUM_INSTRUCTIONS; i++)
    assert(memory[i] == program[i]);

  printf("The assertions all had favorable outcomes!\n");

  return 0;
}
