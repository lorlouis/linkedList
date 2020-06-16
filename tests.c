#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "linkedList.h"

/* Node tests */
void test_node_new() {
    /* test MAX_NB_CHILDREN */
    assert(node_new((void*)42, MAX_NB_CHILDREN +1) == 0);
    /* make sure the node is correctly constructed */
    Node *node = node_new((void*)42, 2);
    assert(node != 0);
    assert((intptr_t)node->value == 42);
    int i;
    for(i=0;i<2;i++) assert(node->children[i] == 0);
    /* _node_debug_print(node); */
    node_free(node);
}

void test_ll_append() {
    LinkedList ll = {0,0};
    /* mallocs a new node on the head */
    ll_append(&ll, (void*)42);
    assert(ll.len == 1);
    /* mallocs on the first node */
    ll_append(&ll, (void*)24);
    assert(ll.len == 2);
    /* cleanup (its still dirty, I
     * just want to prevent a mem leak */
    node_free(ll.head->children[1]);
    node_free(ll.head);
}

void test_ll_remove_last() {
    LinkedList ll = {0,0};
    /* make sure that it fails if ll is empty */
    assert(ll_remove_last(&ll) == 0);
    /* free second item */
    ll_append(&ll, (void*)24);
    ll_append(&ll, (void*)42);
    assert(ll_remove_last(&ll) == 1);
    assert(ll.len == 1);
    assert(ll.head != 0);
    assert(ll.head->children[1] == 0);
    /* free head */
    assert(ll_remove_last(&ll) == 1);
    /* _ll_debug_print(&ll); */
}

void test_ll_free_nodes() {
    LinkedList ll = {0,0};
    /* fails on empty linked list */
    assert(ll_free_nodes(&ll) == 0);
    ll_append(&ll, (void*)42);
    ll_append(&ll, (void*)42);
    ll_append(&ll, (void*)42);
    assert(ll.len == 3);
    assert(ll_free_nodes(&ll) == 1);
    assert(ll.len == 0);
}

void test_ll_seek() {
    LinkedList ll = {0, 0};
    assert(ll_seek(&ll, 0) == 0);
    ll_append(&ll, (void*)42);
    assert(ll_seek(&ll, 0)->value == (void*)42);
    ll_remove_last(&ll);
}

void test_ll_get() {
    LinkedList ll = {0, 0};
    assert(ll_seek(&ll, 0) == 0);
    ll_append(&ll, (void*)42);
    assert(ll_get(&ll, 0) == (void*)42);
    ll_remove_last(&ll);
}

void test_ll_insert() {
    LinkedList ll = {0, 0};
    ll_append(&ll,(void*)12);
    ll_append(&ll,(void*)21);
    ll_append(&ll,(void*)44);
    assert(ll_insert(&ll, 0, (void*)42) == 1);
    assert(ll.len == 4);
    assert(ll_get(&ll, 0) == (void*)42);
    assert(ll_get(&ll, 1) == (void*)12);
    assert(ll_insert(&ll, 2, (void*)88) == 1);
    assert(ll_insert(&ll, 50, 0) == 0);
    assert(ll_get(&ll, 2) == (void*)88);
    assert(ll_get(&ll, 1) == (void*)12);
    assert(ll_insert(&ll, 5, 0) == 1);
    assert(ll_get(&ll, 5) == 0);
    ll_free_nodes(&ll);
}

void test_ll_remove_at() {
    LinkedList ll = {0, 0};
    /* fail on index > ll.len */
    assert(ll_remove_at(&ll, 0) == 0);
    /* remove last */
    ll_append(&ll, (void*)42);
    assert(ll_remove_at(&ll, 0) == 1);
    assert(ll.len == 0);
    /* remove head */
    ll_append(&ll, (void*)42);
    ll_append(&ll, (void*)64);
    assert(ll_remove_at(&ll, 0) == 1);
    assert(ll.head->value == (void*)64);
    /* remove somthing in the middle */
    ll_append(&ll, (void*)42);
    ll_append(&ll, (void*)24);
    assert(ll_remove_at(&ll, 1) == 1);
    assert(ll.head->children[1]->value == (void*)24);
    ll_remove_last(&ll);
    ll_remove_last(&ll);
}

void test_ll_pop() {
    LinkedList ll = {0, 0};
    ll_append(&ll, (void*)42);
    assert(ll_pop(&ll) == (void*)42);
    assert(ll.len == 0);
}


int main() {
    puts("testing node_new");
    test_node_new();
    puts("[OK]");

    puts("testing ll_append");
    test_ll_append();
    puts("[OK]");

    puts("testing ll_remove_last");
    test_ll_remove_last();
    puts("[OK]");

    puts("testing ll_seek");
    test_ll_seek();
    puts("[OK]");

    puts("testing ll_get");
    test_ll_get();
    puts("[OK]");

    puts("testing ll_insert");
    test_ll_insert();
    puts("[OK]");

    puts("testing ll_remove_at");
    test_ll_remove_at();
    puts("[OK]");

    puts("testing ll_pop");
    test_ll_pop();
    puts("[OK]");

    puts("testing ll_free_nodes");
    test_ll_free_nodes();
    puts("[OK]");

    return 0;
}
