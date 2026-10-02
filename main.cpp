#include <stdio.h>
#include <malloc.h>

#include "stack.h"
#include "test.h"


int main()
{    
    stack_t stck;

    test_stack_init(&stck);

    test_push(&stck, 's');
    test_push(&stck, 'k');
    test_push(&stck, 'm');

    test_pop(&stck);
    test_pop(&stck);
    test_pop(&stck);
    
    stack_close(&stck);

    printf("Done\n");
    return 0;
}