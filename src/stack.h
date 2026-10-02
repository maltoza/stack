#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define POISON 63
#define STRUCT_CANARY1 -1
#define STRUCT_CANARY2 -2


// тип элементов в стеке
typedef char stck_el;

// ошибки
enum ERRORS
{
    FUNC_OK = 0,        // функция завершена без ошибок
    ERRORS_MEMALLOC,    // ошибка выделения памяти
    ERRORS_EMPTY,       // пустой стек
    ERRORS_INIT,        // ошибка в инициализации стека
    ERRORS_POP,         // ошибка удаления элемента
    ERRORS_PUSH,        // ошибка добавления элемента
    ERRORS_GMEM,        // ошибка изменения размера стека
    ERRORS_DMEM         // ошибка уменьшения памяти
};

// ошибки стека
enum ERRORS_STCK
{
    ERRORS_STCK_OK = 0,     // нет ошибок
    ERRORS_STCK_NULLPTR,    // нулевой указатель на стек
    ERRORS_STCK_CAPACITY,   // ошибка размера стека
    ERRORS_STCK_NUMELEM,    // ошибка количества элементов
    ERRORS_STRUCT_CANARY1,    // ошибка начальной канарейки стека
    ERRORS_STRUCT_CANARY2     // ошибка конечной канарейки стека
};

struct err_t
{
    const char* file;   // имя файла
    const char* func;   // имя функции
    int line;           // номер линии
};

struct stack_t
{
    int      canary_stck1;
    err_t    error;        // ошибки
    stck_el* first_el;     // указатель на первый элемент
    size_t   num_elems;    // количество элементов в стеке
    size_t   capacity;     // размер стека (кол-во ячеек)
    int      canary_stck2;
};

ERRORS stack_init(stack_t* stck, size_t capacity);
void stack_close(stack_t* stck);

ERRORS pop(stack_t* stck);
ERRORS push(stack_t* stck, stck_el elem);
ERRORS get_mem(stack_t* stck);
ERRORS del_mem(stack_t* stck);
ERRORS fill_poison(stack_t* stck, int start);

#endif // STACK_H