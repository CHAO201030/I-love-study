#ifndef __H_THREAD_POOL_H__
#define __H_THREAD_POOL_H__

#include "H_head.h"
#include "H_net.h"
#include "H_block_queue.h"
#include "H_trans_file.h"

typedef struct{
    pthread_t *pthid;           /* 每个线程的TID */
    int thread_num;             /* 线程数量 */
    block_queue_t *block_queue; /* 阻塞队列 */
}thread_pool_t;

thread_pool_t* thread_pool_init(int thread_num);

void distribute_task(thread_pool_t *p_manager, elem_t new_client);

#endif