#include "stack.h"

#ifdef STACK_DEBUG
    #define STCK_ASSERT(stck_ptr) stack_assert((stck_ptr), __FILE__, __FUNCTION__, __LINE__)
#else
    #define STCK_ASSERT(stck_ptr)  
#endif

void stack_assert(stack_t* stck, const char* file_name, const char* func_name, int line);
ERRORS_STCK stack_verificate(stack_t* stck, const char* file_name, const char* func_name, int line);
void stack_print_err(stack_t stck, ERRORS_STCK result);

// завершение работы
void stack_assert(stack_t* stck, const char* file_name, const char* func_name, int line)
{
    ERRORS_STCK result = stack_verificate(stck, file_name, func_name, line);
    stack_print_err(*stck, result);
    assert(result == ERRORS_STCK_OK);
}


// проверкаа стека
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
    else if (stck->canary_stck1 != STRUCT_CANARY1)
    {
        stck->error.file = file_name;
        stck->error.func = func_name;
        stck->error.line = line;
        return ERRORS_STRUCT_CANARY1;
    }
    else if (stck->canary_stck2 != STRUCT_CANARY2)
    {
        stck->error.file = file_name;
        stck->error.func = func_name;
        stck->error.line = line;
        return ERRORS_STRUCT_CANARY2;
    }
    else
    {
        stck->error.file = file_name;
        stck->error.func = func_name;
        stck->error.line = line;
    }

    return ERRORS_STCK_OK;
}

// вывод ошибок в файл
void stack_print_err(stack_t stck, ERRORS_STCK result)
{
    FILE* err = fopen("errors.txt", "a+");

    fprintf (err, "======================================\n");
    if (result == ERRORS_STCK_OK)
    {
        fprintf (err, "            VERIFICATE OK\n");       
    }
    else
    {
        fprintf (err, "            VERIFICATE ERROR\n");
    }
    fprintf (err, "======================================\n");
    fprintf (err, "            INFORMATION:\n");
    fprintf (err, "File name:     %s\n", stck.error.file);
    fprintf (err, "Function name: %s\n", stck.error.func);
    fprintf (err, "Line number:   %d\n", stck.error.line);
    fprintf (err, "---------------------------------------\n");
    fprintf (err, "    num_elems: %d\n", stck.num_elems);
    fprintf (err, "    capacity:  %d\n", stck.capacity);
    fprintf (err, "    struct canary begin:  %d\n", stck.canary_stck1);
    fprintf (err, "    struct canary finish: %d\n", stck.canary_stck2);
    fprintf (err, "    first_el:  %p\n", stck.first_el);
    fprintf (err, "---------------------------------------\n");
    for (size_t i = 0; i < stck.capacity; i++) {
        if (i < stck.num_elems)
        {
            fprintf (err, "       *elem [%d]: %c\n", i, stck.first_el[i]);
        }
        else
        {
            fprintf (err, "        elem [%d]: %c\n", i, stck.first_el[i]);            
        }
    }
    fprintf (err, "======================================\n\n\n");

    fclose(err);
    return;
}


// создание стека
ERRORS stack_init(stack_t* stck, size_t capacity)
{
    FILE* file = fopen("errors.txt", "w");
    fclose(file);

    stck->canary_stck1 = STRUCT_CANARY1;
    stck->canary_stck2 = STRUCT_CANARY2;
    stck->first_el = (stck_el*)calloc(capacity, sizeof(stck_el));
    if (stck->first_el == NULL)
    {
        return ERRORS_MEMALLOC;
    }

    fill_poison(stck, 0);
    stck->num_elems = 0;
    stck->capacity = capacity;

    STCK_ASSERT(stck);

    return FUNC_OK;
}



// удаление стека
void stack_close(stack_t* stck)
{
    free(stck->first_el);
    stck->first_el = NULL;
    stck->capacity = 0;
    stck->num_elems = 0;
    
    return;
}


// удаление элемента из стека
ERRORS pop(stack_t* stck)
{
    STCK_ASSERT(stck);
    
    if (stck->num_elems == 0)
    {
        return ERRORS_EMPTY;
    }
    
    stck->first_el[stck->num_elems - 1] = POISON;
    stck->num_elems--;
    
    if (stck->num_elems < (stck->capacity) / 2 - 1)
    {
        del_mem(stck);
    }
    
    STCK_ASSERT(stck);
    
    return FUNC_OK;
}


// добавление элемента в стек
ERRORS push(stack_t* stck, stck_el elem)
{
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
    void* temp = realloc((void*)stck->first_el, stck->capacity * 2);
    if (temp == NULL) return ERRORS_GMEM;
    
    stck->first_el = (stck_el*)temp;
    stck->capacity = stck->capacity * 2;
    fill_poison(stck, stck->num_elems);

    return FUNC_OK;
}

// уменьшение памяти стека
ERRORS del_mem(stack_t* stck)
{
    void* temp = realloc((void*)stck->first_el, stck->capacity / 2);
    if (temp == NULL) return ERRORS_DMEM;
    
    stck->first_el = (stck_el*)temp;
    stck->capacity = stck->capacity / 2;
    
    return FUNC_OK;
}


// заполнение ядовитыми значениями
ERRORS fill_poison(stack_t* stck, int start)
{
    for(size_t i = start; i < stck->capacity; i++)
    {
        stck->first_el[i] = POISON;
    }

    return FUNC_OK;
}

