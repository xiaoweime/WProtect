#include <udis86.h>
pInstructionList add_instruction_list(pInstructionBlockList block,ud_t *pobj);
pInstructionList add_instruction_list(pInstructionList instruction,ud_t *pobj);
pInstructionBlockList add_instruction_block_list();
pInstructionBlockList add_instruction_block_list(pInstructionList instruction);
void clean_instruction_list(pInstructionList head);
void clean_instruction_block_list();

pInstructionBlockList get_instruction_block_list_head();