#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

// тип элементов в стеке
typedef char stck_el;

// ошибки
enum ERRORS {
    ERRORS_OK = 0,      // функция завершена без ошибок
    ERRORS_MEMALLOC,    // ошибка выделения памяти
    ERRORS_EMPTY,       // пустой стек
};

struct stack_t {
    stck_el* first_el;  // указатель на первый элемент
    size_t   num_elems; // количетво элементов в стеке
    size_t   capacity;  // размер стека (кол-во ячеек)
};

ERRORS stack_init(stack_t* stck, size_t capacity);
ERRORS pop(stack_t* stck);
ERRORS push(stack_t* stck, stck_el elem);
ERRORS get_mem(stack_t* stck);


#endif // STACK_H