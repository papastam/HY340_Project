#ifndef CS340_PROJECT_STACK_H
#define CS340_PROJECT_STACK_H

#include <stdint.h>

typedef void * Stack;


/**
 * @brief Initializes a new Stack object
 * 
 * @return void* 
 */
void* Stack_create(void);

/**
 * @brief Pushes an int to the Stack. The stack can grow exponentially
 * if it is needed (using realloc()).
 * 
 * @param s 
 * @param val 
 * @return EXIT_SUCCESS if realloc() didn't fail, else EXIT_FAILURE
 */
int Stack_push(Stack s, uint64_t val);

/**
 * @brief Pops an int from the given stack if it isn't empty
 * 
 * @param s 
 * @param retVal 
 * @return If the stack is empty, *retVal is set to zero and EXIT_FAILURE
 * is returned, else EXIT_SUCCESS is returned and *retVal is set to
 * the last int in the stack.
 */
int Stack_pop(Stack restrict s, int * restrict retVal);

/**
 * @brief checks if the stack is empty
 * 
 * @param s 
 * @return int 
 */
int Stack_empty(Stack s);


#endif  /* CS340_PROJECT_STACK_H */