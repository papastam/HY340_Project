#include "stack.h"

#include <stdint.h>
#include <stdlib.h>

#define STACK_DEF_LEN 256U

typedef struct {

    uint32_t len;
    uint32_t ci;   // current index

    int64_t *buf;

} __stack_t;


void* Stack_create(void)
{
    __stack_t *stack;

    if ( !(stack = malloc(sizeof(*stack))) )
        return NULL;

    stack->ci  = 0U;
    stack->len = STACK_DEF_LEN;
    stack->buf = NULL;

    if ( !(stack->buf = malloc(STACK_DEF_LEN * sizeof(*stack->buf))) ) {

        free(stack);
        return NULL;
    }

    return stack;
}

int Stack_push(Stack s, long val)
{
    __stack_t *stack = (__stack_t *)(s);

    stack->buf[stack->ci++] = val;

    if ( stack->ci < stack->len )
        return EXIT_SUCCESS;

    void *t;

    if ( !(t = realloc(stack->buf, 2U * stack->len)) )
        return -(EXIT_FAILURE);

    stack->buf = t;
    stack->len *= 2U;

    return EXIT_SUCCESS;
}

int Stack_pop(Stack restrict s, long * restrict retVal)
{
    __stack_t *stack = (__stack_t *)(s);

    if ( !stack->ci ) {  // stack is empty

        *retVal = 0;
        return -(EXIT_FAILURE);
    }

    *retVal = stack->buf[--stack->ci];

    return EXIT_SUCCESS;
}

int Stack_empty(Stack s)
{
    return ((__stack_t *)(s))->ci;
}

