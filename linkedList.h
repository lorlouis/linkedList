#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_NB_CHILDREN 4096

typedef struct Node_s {
    void* value;
    int nb_children;
    struct Node_s **children;
} Node;
/* creates a new Node */
Node* node_new(void*, unsigned int);

/* frees the node and its children array */
void node_free(Node*);

/* prints the node in debug mode */
void _node_debug_print(Node* node);

typedef struct LinkedLists {
    struct Node_s *head;
    int len;
} LinkedList;

#define ll_len(x) (*x.len)

/* append an element at the end of the list */
void ll_append(LinkedList*, void*);

/* retuns the item stored in the list at index */
void* ll_get(LinkedList*, unsigned int);

/* self explanatory... */
int ll_remove_last(LinkedList*);

/* frees the nodes that the linked list contains */
int ll_free_nodes(LinkedList*);

/* gets a pointer to the node at index n or 0 */
Node* ll_seek(LinkedList*, unsigned int);

/* removes at index, returns 1 if error */
int ll_remove_at(LinkedList*, unsigned int);

/* removes last and returns it */
void* ll_pop(LinkedList* ll);
#endif
