#include <stdlib.h>
#include "node.h"

#ifdef _DEBUG_
#include <stdio.h>
#endif

/* allocates memory for node and node.children
 * and initialises node.children to zeros
 * on fail, returns 0 and sets *err to an errno */
Node* node_new(void* value, unsigned int nb_children, int *err) {
    *err = 0;
    if(nb_children > MAX_NB_CHILDREN){
        *err = 75; /* Value too large for defined data type */
        return 0;
    }
    Node *local_node = malloc(sizeof(Node));
    if(!local_node){
        *err = 12; /* Cannot allocate memory */
        return 0;
    }
    local_node->value = value;
    local_node->nb_children = nb_children;
    local_node->children = calloc(nb_children, sizeof(Node*));
    return local_node;
}

void node_free(Node* node) {
    free(node->children);
    free(node);
}
#ifdef _DEBUG_
void _node_debug_print(Node* node) {
    if(node == 0) {
        printf("Null ptr\n");
        return;
    }
    printf("addr: %p\n", node);
    printf("val: %p\n", node->value);
    printf("children [");
    Node* p;
    while((p = *(node->children))) printf("  %p,\n", p);
    puts("]");
}
#endif
