#include "../include/H_block_queue.h"

block_queue_t* block_queue_create(void)
{
    block_queue_t *q = calloc(1, sizeof(block_queue_t));
    if(q == NULL)
    {
        error(-1, errno, "block_queue_create failed\n");
    }

    if(pthread_mutex_init(&q->mutex, NULL) != 0)
    {
        error(-1, errno, "block_queue_mutex init failed\n");
    }

    if(pthread_cond_init(&q->not_empty, NULL) != 0)
    {
        error(-1, errno, "block_queue_cond_not_empty init failed\n");
    }

    if(pthread_cond_init(&q->not_full, NULL) != 0)
    {
        error(-1, errno, "block_queue_cond_not_full init failed\n");
    }

    return q;
}

elem_t block_queue_pop(block_queue_t* q)
{
    pthread_mutex_lock(&q->mutex);
    
    while(q->size == 0)
    {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    elem_t val = q->elements[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->size--;

    pthread_cond_signal(&q->not_full);

    pthread_mutex_unlock(&q->mutex);

    return val;
}

elem_t block_queue_peek(block_queue_t* q)
{
    pthread_mutex_lock(&q->mutex);
    
    while(q->size == 0)
    {
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }

    elem_t val = q->elements[q->front];

    pthread_mutex_unlock(&q->mutex);

    return val;    
}

void block_queue_push(block_queue_t* q, elem_t val)
{
    pthread_mutex_lock(&q->mutex);
    
    while(q->size == QUEUE_SIZE)
    {
        pthread_cond_wait(&q->not_full, &q->mutex);
    }

    q->elements[q->rear] = val;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->size++;

    pthread_cond_signal(&q->not_empty);

    pthread_mutex_unlock(&q->mutex);
}

void block_queue_destroy(block_queue_t* q)
{
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->not_empty);
    pthread_cond_destroy(&q->not_full);

    free(q);
}

bool block_queue_is_empty(block_queue_t* q)
{
    pthread_mutex_lock(&q->mutex);
    bool result = q->size == 0 ? true : false;
    pthread_mutex_unlock(&q->mutex);

    return result;
}

bool block_queue_is_full(block_queue_t* q)
{
    pthread_mutex_lock(&q->mutex);
    bool result = q->size == QUEUE_SIZE ? true : false;
    pthread_mutex_unlock(&q->mutex);

    return result;
}
