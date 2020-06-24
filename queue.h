#ifndef QUEUE_H
#define QUEUE_H

#include "linkedList.h"

#define Queue LinkedList

#define q_enqueue(queue_p, value, err_p) ll_enqueue(queue_p, value, err_p)

#define q_dequeue(queue_p, err_p) ll_pop(queue_p, err_p)

#endif
