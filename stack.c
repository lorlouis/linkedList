#include "node.h"
#include "linkedList.h"
#include "stack.h"


/* Stack is a macro equivalent to LinkedList */

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
