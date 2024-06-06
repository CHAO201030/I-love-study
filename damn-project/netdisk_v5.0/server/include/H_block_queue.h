#ifndef __H_BLOCK_QUEUE_H__
#define __H_BLOCK_QUEUE_H__

#include "H_head.h"

#define QUEUE_SIZE 1024

typedef struct{
    int fd;
    time_t conn_time;
}elem_t;

typedef struct{
    int front;                  /* 队头 */
    int rear;                   /* 队尾 */
    int size;                   /* 队列大小 */
    pthread_mutex_t mutex;      /* 队列锁 */
    pthread_cond_t not_empty;   /* 非空条件变量 */
    pthread_cond_t not_full;    /* 非满条件变量 */
    elem_t elements[QUEUE_SIZE];/* 循环队列 */
}block_queue_t;


block_queue_t* block_queue_create(void);

elem_t block_queue_pop(block_queue_t* q);

elem_t block_queue_peek(block_queue_t* q);

void block_queue_push(block_queue_t* q, elem_t val);

void block_queue_destroy(block_queue_t* q);

bool block_queue_is_empty(block_queue_t* q);

bool block_queue_is_full(block_queue_t* q);


#endif