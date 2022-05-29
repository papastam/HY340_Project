#ifndef CS340_PROJECT_TARGET_CODE_GEN_H
#include "quads.h"
#include "../../vm/inc/vmalpha.h"

struct incomplete_jump{
    unsigned                instrNo;
    unsigned                iaddress;
    struct incomplete_jump* next;
};

typedef void (*generator_func_t) (struct quad*);

void generate_ASSIGN(struct quad*);             
void generate_ADD(struct quad*);         
void generate_SUB(struct quad*);
void generate_MUL(struct quad*);
void generate_DIV_O(struct quad*);
void generate_MOD(struct quad*);
void generate_UMINUS(struct quad*);
void generate_AND_O(struct quad*);
void generate_OR_O(struct quad*);
void generate_NOT_O(struct quad*);
void generate_IF_EQ(struct quad*);
void generate_IF_NOTEQ(struct quad*);
void generate_IF_LESSEQ(struct quad*);
void generate_IF_GREATEREQ(struct quad*);
void generate_IF_LESS(struct quad*);
void generate_IF_GREATER(struct quad*);
void generate_CALL(struct quad*);
void generate_PARAM(struct quad*);
void generate_RET(struct quad*);
void generate_GETRETVAL(struct quad*);
void generate_FUNCSTART(struct quad*);
void generate_FUNCEND(struct quad*);
void generate_TABLECREATE(struct quad*);
void generate_TABLEGETELEM(struct quad*);
void generate_TABLESETELEM(struct quad*);
void generate_JUMP(struct quad*);

int consts_newstring(char*);
int consts_newnum(double);
int libfuncs_newused(char*);

void generate(void);
void make_operand(struct expr*, struct vmarg*);
void emit_tcode(struct vminstruction *instr);

extern struct vminstruction * instructions;
extern uint totalinstr;
extern uint currInstr;

#define INSTRUCTION_EXPAND_SIZE 512 * sizeof(struct vminstruction)
#define CURR_ISNTR_SIZE   (total*sizeof(struct vminstruction))
#define NEW_INSTR_SIZE    (INSTRUCTION_EXPAND_SIZE + CURR_ISNTR_SIZE)
#define INSTR_INIT_SIZE 256

#endif