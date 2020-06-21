#include "node.h"
#include "linkedList.h"
#include "stack.h"


/* Stack is a macro equivalent to LinkedList
 * node.children[0] only references the next node */

/* pushes the value on the head of the linked list */
int stk_push(Stack* stk, void* value) {
    Node* node = node_new(value, 1);
    if(stk->head) {
        node->children[0] = stk->head;
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
    Node* node = stk->head->children[0];
    node_free(stk->head);
    stk->head = node;
    return val;
}
