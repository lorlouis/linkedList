#include "node.h"
#include "linkedList.h"
#include "stack.h"


/* Stack is a macro equivalent to LinkedList */

/* pushes the value on the head of the linked list */
int stk_push(Stack* stk, void* value, int *err) {
    *err = 0;
    /* 2 children because I want ll_*
     * methods to work on stacks*/
    Node* node = node_new(value, 2, err);
    if(*err) return -1;

    if(stk->head) {
        node->children[1] = stk->head;
    }
    stk->head = node;
    stk->len++;
    return 0;
}
/* pops, the value present on the head of the stack
 * on fail it return 0 and writes an errno to *err */
void* stk_pop(Stack* stk, int* err) {
    *err = 0;
    if(!stk || !stk->head) {
        *err = -1;
        return 0;
    }
    void* val = stk->head->value;
    Node* node = stk->head->children[1];
    node_free(stk->head);
    stk->head = node;
    return val;
}
