#ifndef TEST_H
#define TEST_H

#include "stack.h"

ERRORS test_stack_init(stack_t* stck);
ERRORS test_push(stack_t* stck, stck_el symb);
ERRORS test_pop(stack_t* stck);

#endif // TEST_H