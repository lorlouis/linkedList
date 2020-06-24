#ifndef STACK_H
#define STACK_H

#include "linkedList.h"

/* Stack is a macro equivalent to LinkedList */
#define Stack LinkedList

#define stk_push(stack_p, val, err_p) ll_enqueue(stack_p, val, err_p)

void* stk_pop(Stack*, int*);
#endif
