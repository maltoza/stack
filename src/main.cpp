#include <stdio.h>
#include <malloc.h>
#include "stack.h"


int main()
{
    stack_t stck;

    ERRORS result = stack_init(&stck, 10);
    if (result != ERRORS_OK) return result;
    printf("%s %d %d\n", stck.first_el, stck.capacity, stck.num_elems);

    result = push(&stck, 's');
    if (result != ERRORS_OK) return result;
    printf("%s %d %d\n", stck.first_el, stck.capacity, stck.num_elems);

    result = push(&stck, 'k');
    if (result != ERRORS_OK) return result;
    printf("%s %d %d\n", stck.first_el, stck.capacity, stck.num_elems);

    result = push(&stck, 'm');
    if (result != ERRORS_OK) return result;
    printf("%s %d %d\n", stck.first_el, stck.capacity, stck.num_elems);

    result = pop(&stck);
    if (result != ERRORS_OK) return result;
    printf("%s %d %d\n", stck.first_el, stck.capacity, stck.num_elems);

    result = pop(&stck);
    if (result != ERRORS_OK) return result;
    printf("%s %d %d\n", stck.first_el, stck.capacity, stck.num_elems);

    free((void*)&stck);

    printf("Done\n");
    return 0;
}