#ifndef STACK_H
#define STACK_H

#include "linkedList.h"

#define Stack LinkedList

int stk_push(Stack*, void*, int*);

void* stk_pop(Stack*, int*);
#endif
