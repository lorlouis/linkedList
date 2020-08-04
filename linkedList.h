#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"

typedef struct LinkedLists {
    struct Node_s *head, *tail;
    int len;
} LinkedList;

#define ll_len(x) (*x.len)

/* append an element at the end of the list */
int ll_append(LinkedList*, void*, int*);

/* pushes the value on the head of the linked list */
int ll_enqueue(LinkedList*, void*, int*);

/* insert at a specific index */
int ll_insert(LinkedList* ,int, void*, int *);

/* retuns the item stored in the list at index
 * on error returns NULL and sets *err to an errno */
void* ll_get(LinkedList*, int, int*);

/* self explanatory... */
int ll_remove_last(LinkedList* , int* );

/* frees the nodes that the linked list contains */
int ll_free_nodes(LinkedList *, int *);

/* gets a pointer to the node at index n or 0 */
Node* ll_seek(LinkedList* , int , int *);

/* removes at index, returns 1 if error */
int ll_remove_at(LinkedList* , int , int *);

/* removes last and returns it
 * on error returns NULL and sets *err to and errno */
void* ll_pop(LinkedList* , int *);
#endif
