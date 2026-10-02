#include "stack.h"

#ifdef STACK_DEBUG
    #define STCK_ASSERT(stck_ptr) do {  \
        stack_assert((stck_ptr), __FILE__, __FUNCTION__, __LINE__); \
    } while(0)
#else
    #define STCK_ASSERT(stck_ptr)  do {} while(0)
#endif

void stack_assert(stack_t* stck, const char* file_name, const char* func_name, int line);
ERRORS_STCK stack_verificate(stack_t* stck, const char* file_name, const char* func_name, int line);
void stack_print_err(stack_t stck, ERRORS_STCK result);


void stack_assert(stack_t* stck, const char* file_name, const char* func_name, int line)
{
    ERRORS_STCK result = stack_verificate(stck, file_name, func_name, line);
    stack_print_err(*stck, result);
    assert(result == ERRORS_STCK_OK);
}



ERRORS_STCK stack_verificate(stack_t* stck, const char* file_name, const char* func_name, int line)
{
    if (stck == NULL)
    {
        stck->error.file = file_name;
        stck->error.func = func_name;
        stck->error.line = line;
        return ERRORS_STCK_NULLPTR;
    }
    else if (stck->capacity == 0)
    {
        stck->error.file = file_name;
        stck->error.func = func_name;
        stck->error.line = line;
        return ERRORS_STCK_CAPACITY;
    }
    else if (stck->num_elems > stck->capacity)
    {
        stck->error.file = file_name;
        stck->error.func = func_name;
        stck->error.line = line;  
        return ERRORS_STCK_NUMELEM;
    }
    else if (stck->canary_stck1 != STCK_CANARY1)
    {
        stck->error.file = file_name;
        stck->error.func = func_name;
        stck->error.line = line;
        return ERRORS_STCK_CANARY1;
    }
    else if (stck->canary_stck2 != STCK_CANARY2)
    {
        stck->error.file = file_name;
        stck->error.func = func_name;
        stck->error.line = line;
        return ERRORS_STCK_CANARY2;
    }
    else
    {
        stck->error.file = file_name;
        stck->error.func = func_name;
        stck->error.line = line;
    }

    return ERRORS_STCK_OK;
}


void stack_print_err(stack_t stck, ERRORS_STCK result)
{
    FILE* err = fopen("errors.txt", "a+");

    fprintf (err, "======================================\n");
    if (result == ERRORS_STCK_OK)
    {
        fprintf (err, "           VERIFICATE OK\n");       
    }
    else
    {
        fprintf (err, "           VERIFICATE ERROR\n");
    }
    fprintf (err, "======================================\n");
    fprintf (err, "INFORMATION:\n");
    fprintf (err, "File name:     %s\n", stck.error.file);
    fprintf (err, "Function name: %s\n", stck.error.func);
    fprintf (err, "Line number:   %d\n", stck.error.line);
    fprintf (err, "---------------------------------------\n");
    fprintf (err, "    num_elems: %d\n", stck.num_elems);
    fprintf (err, "    capacity:  %d\n", stck.capacity);
    fprintf (err, "    stack canary1: %d\n", stck.canary_stck1);
    fprintf (err, "    stack canary2: %d\n", stck.canary_stck2);
    fprintf (err, "    first_el:  %p\n", stck.first_el);
    fprintf (err, "---------------------------------------\n");
    for (size_t i = 0; i < stck.num_elems; i++) {
        fprintf (err, "        elem [%d]: %c\n", i, stck.first_el[i]);
    }
    fprintf (err, "======================================\n\n\n");

    fclose(err);
    return;
}


// создание стека
ERRORS stack_init(stack_t* stck, size_t capacity)
{
    assert(stck != NULL);

    FILE* file = fopen("errors.txt", "w");
    fclose(file);

    stck->canary_stck1 = STCK_CANARY1;
    stck->canary_stck2 = STCK_CANARY2;
    stck->first_el = (stck_el*)calloc(capacity, sizeof(stck_el));
    if (stck->first_el == NULL)
    {
        return ERRORS_MEMALLOC;
    }

    stck->num_elems = 0;
    stck->capacity = capacity;

    STCK_ASSERT(stck);

    return FUNC_OK;
}



void stack_close(stack_t* stck)
{
    assert(stck != NULL);
    
    free(stck->first_el);
    stck->first_el = NULL;
    stck->capacity = 0;
    stck->num_elems = 0;

    return;
}


// удаление элемента
ERRORS pop(stack_t* stck)
{
    assert(stck != NULL);

    STCK_ASSERT(stck);

    if (stck->num_elems == 0)
    {
        return ERRORS_EMPTY;
    }

    stck->first_el[stck->num_elems - 1] = '\0';
    stck->num_elems--;

    if (stck->num_elems < stck->capacity / 2 - 1)
    {
        del_mem(stck);
    }

    STCK_ASSERT(stck);

    return FUNC_OK;
}


// добавление элемента
ERRORS push(stack_t* stck, stck_el elem)
{
    assert(stck != NULL);

    STCK_ASSERT(stck);

    if (stck->num_elems == stck->capacity)
    {
        get_mem(stck);
    }
    stck->first_el[stck->num_elems] = elem;
    stck->num_elems++;

    STCK_ASSERT(stck);

    return FUNC_OK;
}


// увеличение памяти стека
ERRORS get_mem(stack_t* stck)
{
    assert(stck != NULL);

    void* temp = realloc((void*)stck, stck->capacity * 2);
    if (temp == NULL) return ERRORS_GMEM;

    stck->first_el = (stck_el*)temp;
    stck->capacity = stck->capacity * 2;

    return FUNC_OK;
}

// уменьшение памяти стека
ERRORS del_mem(stack_t* stck)
{
    assert(stck != NULL);

    void* temp = realloc((void*)stck, stck->capacity / 2);
    if (temp == NULL) return ERRORS_GMEM;

    stck->first_el = (stck_el*)temp;
    stck->capacity = stck->capacity / 2;

    return FUNC_OK;
}


