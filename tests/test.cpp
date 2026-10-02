#include "test.h"

ERRORS test_stack_init(stack_t* stck)
{
    ERRORS result = stack_init(stck, 10);
    if (result != FUNC_OK) return result;
    printf("%s %d %d\n", stck->first_el, stck->capacity, stck->num_elems);

    return result;
}



ERRORS test_push(stack_t* stck, char symb)
{
    ERRORS result = push(stck, symb);
    if (result != FUNC_OK) return result;
    printf("%s %d %d\n", stck->first_el, stck->capacity, stck->num_elems);

    return result;
}



ERRORS test_pop(stack_t* stck)
{
    ERRORS result = pop(stck);
    if (result != FUNC_OK) return result;
    printf("%s %d %d\n", stck->first_el, stck->capacity, stck->num_elems);

    return result;
}
