#ifndef NODE_H
#define NODE_H

#define MAX_NB_CHILDREN 4096

typedef struct Node_s {
    void* value;
    int nb_children;
    struct Node_s **children;
} Node;
/* creates a new Node */
Node* node_new(void* , unsigned int , int *);

/* frees the node and its children array */
void node_free(Node*);
#ifdef _DEBUG_
/* prints the node in debug mode */
void _node_debug_print(Node*);
#endif
#endif
