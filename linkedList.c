#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"

/* allocates memory for node and node.children
 * and initialises node.children to zeros */
Node* node_new(void* value, unsigned int nb_children) {
    if(nb_children > MAX_NB_CHILDREN)
        return 0;

    Node *local_node = malloc(sizeof(Node));
    local_node->value = value;
    local_node->nb_children = nb_children;
    local_node->children = calloc(nb_children, sizeof(Node*));
    return local_node;
}

void node_free(Node* node) {
    free(node->children);
    free(node);
}

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

/* allocates memory on ll_node and ll_node.children
 * (ll_node.children is initialised to a bunch of zeros */
void ll_push(LinkedList* ll, void* value) {
    Node *ll_node = node_new(value, 2);
    /* check if we push to the head */
    if(!ll->len) {
        ll->head = ll_node;
        ll->len += 1;
        return;
    }
    int i;
    Node *current = ll->head;
    for(i=1;i<ll->len;i++)
        current = current->children[1];

    ll_node->children[0] = current;
    current->children[1] = ll_node;
    ll->len += 1;
}

/* TODO rework to remove edge cases */
int ll_remove_last(LinkedList* ll) {
    if(!ll || ll->len == 0 || !ll->head)
        return 0;

    ll->len--;
    if(ll->len == 0) {
        node_free(ll->head);
        return 1;
    }

    Node *current = ll->head;
    while(current->children[1]) {
        current = current->children[1];
    }
    /* remove ref to current in prev Node */
    current->children[0]->children[1] = 0;
    node_free(current);
    return 1;
}

int ll_free_nodes(LinkedList *ll) {
    if(!ll || ll->len == 0 || !ll->head)
        return 0;
    while(ll_remove_last(ll));
    return ll->len == 0;
}

Node* ll_seek(LinkedList* ll, unsigned int index) {
    /* out of bound */
    if(index >= ll->len) return 0;

    Node *ll_node = ll->head;
    while(index--) ll_node = ll_node->children[1];
    return ll_node;
}

int ll_remove_at(LinkedList* ll, unsigned int index) {
    if(index >= ll->len) return 0;
    if(index == ll->len-1) return ll_remove_last(ll);
    Node *tmp;
    
    /* remove head */
    if(index == 0) {
        tmp = ll->head;
        if(ll->head->children[1])
            ll->head = ll->head->children[1];
        node_free(tmp);
        ll->len--;
        return 1;
    }
    /* remove any other index */
    tmp = ll_seek(ll, index);

    /* children[0] = previous node
     * children[1] = next node
     * this changes the next node of the previous node
     * to be the next node of tmp */
    tmp->children[0]->children[1] = tmp->children[1];
    ll->len--;
    node_free(tmp);
    return 1;
}

void* ll_get(LinkedList* ll, unsigned int index) {
    Node* ll_node = ll_seek(ll, index);
    return ll_node->value;
}

void* ll_pop(LinkedList* ll) {
    void *val = ll_get(ll, ll->len - 1);
    ll_remove_last(ll);
    return val;
}

void _ll_debug_print(LinkedList* ll) {
    printf("len: %d\n[", ll->len);
    Node* cur = ll->head;
    while(cur != 0) {
        printf("%p, ", cur->value);
        cur = cur->children[1];
    }
    printf("]\n");
}
