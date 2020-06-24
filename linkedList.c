#include <stdlib.h>
#ifdef _DEBUG_
#include <stdio.h>
#endif
#include "node.h"
#include "linkedList.h"

/* TODO IMPLEMENT TAIL EVERYWHERE AND OPTIMISE FOR IT */

/* returns a pointer to the node,
 * returns 0 if the seek fails
 * and writes an errno to *err */
Node* ll_seek(LinkedList* ll, unsigned int index, int *err) {
    *err = 0;
    /* out of bound */
    if(index >= ll->len){
        *err = 29;  /* illegal seek */
        return NULL;
    }
    /* dir:= 0 backwards dir:= 1 forward */
    int dir = (index < ll->len/2);
    Node *ll_node = ll->head;
    /* if the index is closer to the
     * tail than the head */
    if(!dir) {
        ll_node = ll->tail;
        index = (ll->len-1) - index;
    }
    while(index--) ll_node = ll_node->children[dir];

    return ll_node;
}

/* pushes the value on the head of the linked list */
int ll_enqueue(LinkedList *ll, void* value, int *err) {
    *err = 0;
    Node* node = node_new(value, 2, err);
    if(*err) return -1;

    if(ll->head) {
        ll->head->children[0] = node;
        node->children[1] = ll->head;
    }
    if(!ll->len) ll->tail = node;
    ll->head = node;
    ll->len++;
    return 0;
}

int ll_insert(LinkedList* ll, unsigned int index, void* value, int *err) {
    *err = 0;
    /* check if we append */
    if(index == ll->len) {
        ll_append(ll, value, err);
        return 0;
    }
    /* you cannot insert to an unreachable index */
    if(index > ll->len) {
        *err = 29;  /* Illegal seek */
        return -1;
    }

    /* if we insert on the head */
    if(!index) {
        ll_enqueue(ll, value, err);
        return *err ? -1 : 0;
    }
    Node *ll_node = node_new(value, 2, err);
    if(*err) return -1;
    Node *current = ll_seek(ll, index, err);
    ll_node->children[0] = current->children[0];

    current->children[0]->children[1] = ll_node;

    ll_node->children[1] = current;
    current->children[0] = ll_node;
    ll->len++;
    return 0;
}

/* allocates memory on ll_node and ll_node.children
 * (ll_node.children is initialised to a bunch of zeros)
 * on fail it returns -1 and sets *err to and errno */
int ll_append(LinkedList* ll, void* value, int *err) {
    /* node_new sets *err to 0 before using it */
    Node *ll_node = node_new(value, 2, err);
    if(*err) return -1;
    /* check if we push to the head */
    if(!ll->len) {
        ll->head = ll_node;
        ll->tail = ll_node;
        ll->len++;
        return 0;
    }
    int i;
    Node *current = ll->head;
    for(i=0;i<ll->len-1;i++)
        current = current->children[1];

    ll_node->children[0] = current;
    current->children[1] = ll_node;
    ll->tail = ll_node;
    ll->len++;
    return 0;
}

/* TODO rework to use tail instead of head */
/* removes the last element in the linked list
 * on fail, it returns -1 and sets *err to and errno */
int ll_remove_last(LinkedList* ll, int* err) {
    *err = 0;
    if(!ll || ll->len == 0 || !ll->head || !ll->tail) {
        *err = 29;  /* Illegal seek */
        return -1;
    }

    ll->len--;
    if(ll->len == 0) {
        node_free(ll->head);
        ll->head = 0;
        ll->tail = 0;
        return 0;
    }

    Node *current = ll->tail;
    /* remove ref to current in prev Node */
    if(current->children[0]) {
        current->children[0]->children[1] = 0;
    }
    ll->tail = current->children[0];
    node_free(current);
    return 0;
}

int ll_free_nodes(LinkedList *ll, int *err) {
    *err = 0;
    if(!ll || ll->len == 0 || !ll->head) {
        *err = 29;  /* Illegal seek */
        return -1;
    }
    /* on error remove_last will set err to Illegal seek */
    while(ll_remove_last(ll, err) == 0);
    return ll->len ? -1 : 0;
}

int ll_remove_at(LinkedList* ll, unsigned int index, int *err) {
    *err = 0;
    if(index >= ll->len){
        *err = 29;  /* Illegal seek */
        return -1;
    }
    if(index == ll->len-1) return ll_remove_last(ll, err);
    Node *tmp;
    
    /* remove head */
    if(index == 0) {
        tmp = ll->head;
        if(ll->head->children[1]) {
            ll->head = ll->head->children[1];
            ll->head->children[0] = 0;
        }
        node_free(tmp);
        ll->len--;
        if(!ll->len) ll->tail = 0;
        return 0;
    }
    /* remove any other index */
    tmp = ll_seek(ll, index, err);
    if(*err) return -1;

    /* children[0] = previous node
     * children[1] = next node
     * this changes the next node of the previous node
     * to be the next node of tmp */
    tmp->children[0]->children[1] = tmp->children[1];
    tmp->children[1]->children[0] = tmp->children[0];
    ll->len--;
    node_free(tmp);
    return 0;
}

/* returns the value stored at index in the linked list
 * on fail it returns NULL and write an errno to *err */
void* ll_get(LinkedList* ll, unsigned int index, int* err) {
    /* ll_seek sets *err to 0, no use to set it here */
    Node* ll_node = ll_seek(ll, index, err);
    if(*err) return 0;
    return ll_node->value;
}

/* removes and returns the value of the last
 * element in the list
 * returns NULL if it fails */
void* ll_pop(LinkedList* ll, int *err) {
    void *val = ll_get(ll, ll->len - 1, err);
    if(*err) return 0;
    ll_remove_last(ll, err);
    if(*err) return 0;
    return val;
}
#ifdef _DEBUG_
void _ll_debug_print(LinkedList* ll) {
    printf("len: %d\n[", ll->len);
    Node* cur = ll->head;
    while(cur != 0) {
        printf("%p, ", cur->value);
        cur = cur->children[1];
    }
    printf("]\n");
}
#endif
