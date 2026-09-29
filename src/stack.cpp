#include "stack.h"

// создание стека
ERRORS stack_init(stack_t* stck, size_t capacity)
{
    assert(stck != NULL);
    
    stck->first_el = (stck_el*)calloc(capacity, sizeof(stck_el));
    stck->num_elems = 0;
    
    if (stck->first_el == NULL) {
        return ERRORS_MEMALLOC;
    }

    return ERRORS_OK;
}


// удаление элемента
ERRORS pop(stack_t* stck)
{
    assert(stck != NULL);
    if (stck->num_elems == 0) {
        return ERRORS_EMPTY;
    }

    stck->first_el[stck->num_elems - 1] = '\0';
    stck->num_elems--;

    return ERRORS_OK;
}


// добавление элемента
ERRORS push(stack_t* stck, stck_el elem)
{
    assert(stck != NULL);

    stck->first_el[stck->num_elems] = elem;
    stck->num_elems++;

    return ERRORS_OK;
}
