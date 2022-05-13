#ifndef CS340_PROJECT_STACK_H
#define CS340_PROJECT_STACK_H

#include <stdint.h>

#define STACK_DEF_LEN (256 * sizeof(int))

typedef struct {

    uint32_t len;

    uint32_t ci;  // current index
    uint32_t fp;  // frame pointer

} Stack;



#endif  /* CS340_PROJECT_STACK_H */