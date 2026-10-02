#include <stdio.h>
#include <malloc.h>

#include "stack.h"
#include "test.h"


int main()
{    
    stack_t stck;

    stack_init(&stck, 1);

    push(&stck, 's');
    push(&stck, 'k');
    push(&stck, 'm');

    pop(&stck);
    pop(&stck);
    pop(&stck);
    
    stack_close(&stck);

    printf("Done\n");
    return 0;
}