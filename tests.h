#ifndef TESTS_H
#define TESTS_H 1

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#include "linkedList.h"
#include "stack.h"
#include "queue.h"

#define testing(str, fn) {\
    puts(str);\
    fn();\
    puts("\033[32m[OK]\033[0m");\
}

/* Node tests */
void test_node_new(void);

void test_ll_enqueue(void);

void test_ll_append(void);

void test_ll_remove_last(void);

void test_ll_free_nodes(void);

void test_ll_seek(void);

void test_ll_get(void);

void test_ll_insert(void);

void test_ll_remove_at(void);

void test_ll_pop(void);

void test_stk_push(void);

void test_stk_pop(void);

void test_q_enqueue(void);

void test_q_dequeue(void);

int main(void);
#endif
