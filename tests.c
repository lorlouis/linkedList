#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#include "linkedList.h"
#include "stack.h"
#include "queue.h"

#define testing(str, fn) { \
printf(str);\
fn();\
puts("\033[32m[OK]\033[0m");\
}

/* Node tests */
void test_node_new() {
    int err = 0;
    /* test MAX_NB_CHILDREN */
    assert(node_new((void*)42, MAX_NB_CHILDREN +1, &err) == 0);
    assert(err == 75);
    /* make sure the node is correctly constructed */
    Node *node = node_new((void*)42, 2, &err);
    assert(node != 0);
    assert(err == 0);
    assert((intptr_t)node->value == 42);
    int i;
    for(i=0;i<2;i++) assert(node->children[i] == 0);
    node_free(node);
}

void test_ll_enqueue() {
    int err = 0;
    /* init linked list */
    LinkedList ll = {0};
    ll_enqueue(&ll, (void*)42, &err);
    assert(err == 0);
    assert(ll.head->value == (void*)42);
    assert(ll.tail->value == (void*)42);
    assert(ll.head->children[0] == 0);
    assert(ll.head->children[1] == 0);
    assert(ll.len == 1);
    ll_enqueue(&ll, (void*)24, &err);
    assert(ll.head->value == (void*)24);
    assert(ll.tail->value == (void*)42);
    assert(ll.head->children[1]->value == (void*)42);
    assert(ll.tail->children[0]->value == (void*)24);
    assert(ll.len == 2);
    ll_free_nodes(&ll, &err);
    assert(err == 0);
}

void test_ll_append() {
    int err;
    LinkedList ll = {0};
    /* mallocs a new node on the head */
    ll_append(&ll, (void*)42, &err);
    assert(err == 0);
    assert(ll.len == 1);
    assert(ll.head->value == (void*)42);
    assert(ll.tail->value == (void*)42);
    assert(ll.head->children[0] == 0);
    assert(ll.head->children[1] == 0);
    /* mallocs on the first node */
    ll_append(&ll, (void*)24, &err);
    assert(err == 0);
    assert(ll.head->value == (void*)42);
    assert(ll.head->children[1]->value == (void*)24);
    assert(ll.tail->value == (void*)24);
    assert(ll.tail->children[0]->value == (void*)42);
    assert(ll.len == 2);
    /* cleanup */
    ll_free_nodes(&ll, &err);
    assert(err == 0);
}

void test_ll_remove_last() {
    int err;
    LinkedList ll = {0};
    /* make sure that it fails if ll is empty */
    assert(ll_remove_last(&ll, &err) == -1);
    assert(err == 29);
    /* free second item */
    ll_append(&ll, (void*)24, &err);
    ll_append(&ll, (void*)42, &err);
    assert(ll_remove_last(&ll, &err) == 0);
    assert(err == 0);
    assert(ll.tail->value == (void*)24);
    assert(ll.head->value == (void*)24);
    assert(ll.len == 1);
    assert(ll.head->children[1] == 0);
    assert(ll.head->children[0] == 0);
    assert(ll.tail == ll.head);
    /* cleanup */
    assert(ll_remove_last(&ll, &err) == 0);
    assert(err == 0);
    assert(ll.head == 0);
    assert(ll.tail == 0);
    assert(ll.len == 0);
    /* _ll_debug_print(&ll); */
}

void test_ll_free_nodes() {
    int err;
    LinkedList ll = {0};
    /* fails on empty linked list */
    assert(ll_free_nodes(&ll, &err) == -1);
    assert(err == 29);
    ll_append(&ll, (void*)42, &err);
    ll_append(&ll, (void*)42, &err);
    ll_append(&ll, (void*)42, &err);
    assert(ll.len == 3);
    assert(ll_free_nodes(&ll, &err) == 0);
    assert(ll.len == 0);
    assert(ll.head == 0);
    assert(ll.tail == 0);
}

void test_ll_seek() {
    int err;
    LinkedList ll = {0};
    assert(ll_seek(&ll, 0, &err) == 0);
    assert(err == 29);
    ll_append(&ll, (void*)42, &err);
    assert(ll_seek(&ll, 0, &err)->value == (void*)42);
    assert(err == 0);
    ll_append(&ll, (void*)24, &err);
    assert(ll_seek(&ll, 1, &err)->value == (void*)24);
    assert(err == 0);
    /* cleanup */
    assert(ll_free_nodes(&ll, &err) == 0);
    assert(err == 0);
}

void test_ll_get() {
    int err;
    LinkedList ll = {0};
    assert(ll_get(&ll, 0, &err) == 0);
    assert(err == 29);
    ll_append(&ll, (void*)42, &err);
    assert(ll_get(&ll, 0, &err) == (void*)42);
    assert(err == 0);
    ll_append(&ll, (void*)24, &err);
    assert(ll_get(&ll, 1, &err) == (void*)24);
    assert(err == 0);
    ll_append(&ll, (void*)64, &err);
    assert(ll_get(&ll, 2, &err) == (void*)64);
    assert(err == 0);
    /* cleanup */
    assert(ll_free_nodes(&ll, &err) == 0);
    assert(err == 0);
}

void test_ll_insert() {
    int err;
    LinkedList ll = {0};
    ll_append(&ll,(void*)12, &err);
    ll_append(&ll,(void*)21, &err);
    ll_append(&ll,(void*)44, &err);
    assert(ll_insert(&ll, 0, (void*)42, &err) == 0);
    assert(err == 0);
    assert(ll.len == 4);
    /* test insert stuff */
    assert(ll_get(&ll, 0, &err) == (void*)42);
    assert(ll_get(&ll, 1, &err) == (void*)12);
    assert(ll_insert(&ll, 2, (void*)88, &err) == 0);
    assert(err == 0);
    assert(ll.len == 5);
    /* test insert at unreachable index */
    assert(ll_insert(&ll, 50, 0, &err) == -1);
    assert(err == 29);
    assert(ll.len == 5);
    /* make sure we didn't insert something anyway */
    assert(ll_get(&ll, 0, &err) == (void*)42);
    assert(err == 0);
    assert(ll_get(&ll, 1, &err) == (void*)12);
    assert(err == 0);
    assert(ll_get(&ll, 2, &err) == (void*)88);
    assert(err == 0);
    assert(ll_get(&ll, 3, &err) == (void*)21);
    assert(err == 0);
    assert(ll_get(&ll, 4, &err) == (void*)44);
    assert(err == 0);
    /* test insert on tail */
    assert(ll_insert(&ll, 5, (void*)1337, &err) == 0);
    assert(err == 0);
    assert(ll_get(&ll, 5, &err) == (void*)1337);
    assert(err == 0);
    /* cleanup */
    assert(ll_free_nodes(&ll, &err) == 0);
    assert(err == 0);
}

void test_ll_remove_at() {
    int err;
    LinkedList ll = {0};
    /* fail on index > ll.len */
    assert(ll_remove_at(&ll, 0, &err) == -1);
    /* remove last */
    ll_append(&ll, (void*)42, &err);
    assert(ll_remove_at(&ll, 0, &err) == 0);
    assert(ll.len == 0);
    assert(ll.tail == 0);
    /* remove head */
    ll_append(&ll, (void*)42, &err);
    ll_append(&ll, (void*)64, &err);
    assert(ll_remove_at(&ll, 0, &err) == 0);
    assert(ll.head->value == (void*)64);
    /* remove somthing in the middle */
    ll_append(&ll, (void*)42, &err);
    ll_append(&ll, (void*)24, &err);
    assert(ll_remove_at(&ll, 1, &err) == 0);
    assert(ll.head->children[1]->value == (void*)24);
    ll_free_nodes(&ll, &err);
}

void test_ll_pop() {
    int err;
    LinkedList ll = {0};
    ll_append(&ll, (void*)42, &err);
    assert(ll_pop(&ll, &err) == (void*)42);
    assert(ll.len == 0);
    assert(ll.head == 0);
    assert(ll.tail == 0);
}

void test_stk_push() {
    int err;
    /* init linked list */
    Stack stk = {0};
    stk_push(&stk, (void*)42, &err);
    assert(err == 0);
    assert(stk.head->value == (void*)42);
    assert(stk.tail->value == (void*)42);
    assert(stk.head->children[0] == 0);
    assert(stk.head->children[1] == 0);
    assert(stk.len == 1);
    stk_push(&stk, (void*)24, &err);
    assert(stk.head->value == (void*)24);
    assert(stk.tail->value == (void*)42);
    assert(stk.head->children[1]->value == (void*)42);
    assert(stk.tail->children[0]->value == (void*)24);
    assert(stk.len == 2);
    stk_free(&stk, &err);
    assert(err == 0);
}

void test_stk_pop() {
    int err;
    Stack stk = {0};
    stk_push(&stk, (void*)42, &err);
    stk_push(&stk, (void*)24, &err);
    assert(stk_pop(&stk, &err) == (void*)24);
    assert(err == 0);
    assert(stk.tail->value == (void*)42);
    assert(stk_pop(&stk, &err) == (void*)42);
    assert(err == 0);
    assert(stk.tail == 0);
    assert(stk.head == 0);
}

void test_q_enqueue() {
    int err;
    /* init linked list */
    Queue q = {0};
    stk_push(&q, (void*)42, &err);
    assert(err == 0);
    assert(q.head->value == (void*)42);
    assert(q.tail->value == (void*)42);
    assert(q.head->children[0] == 0);
    assert(q.head->children[1] == 0);
    assert(q.len == 1);
    stk_push(&q, (void*)24, &err);
    assert(q.head->value == (void*)24);
    assert(q.tail->value == (void*)42);
    assert(q.head->children[1]->value == (void*)42);
    assert(q.tail->children[0]->value == (void*)24);
    assert(q.len == 2);
    q_free(&q, &err);
    assert(err == 0);
}

void test_q_dequeue() {
    int err;
    Queue q = {0};
    q_enqueue(&q, (void*)42, &err);
    assert(q_dequeue(&q, &err) == (void*)42);
    assert(q.len == 0);
    assert(q.head == 0);
    assert(q.tail == 0);
}

int main() {
    testing("testing node_new", test_node_new);

    testing("testing ll_seek", test_ll_seek);

    testing("testing ll_insert", test_ll_insert);

    testing("testing ll_enqueue", test_ll_enqueue);

    testing("testing ll_append", test_ll_append);

    testing("testing ll_remove_last", test_ll_remove_last);

    testing("testing ll_get", test_ll_get);

    testing("testing ll_remove_at", test_ll_remove_at);

    testing("testing ll_pop", test_ll_pop);

    testing("testing ll_free_nodes", test_ll_free_nodes);

    testing("testing stk_push", test_stk_push);

    testing("testing stk_pop", test_stk_pop);

    testing("testing q_enqueue", test_q_enqueue);

    testing("testing q_dequeue", test_q_dequeue);

    return 0;
}
