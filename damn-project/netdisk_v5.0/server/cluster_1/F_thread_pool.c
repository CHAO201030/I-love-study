#include "../include/H_thread_pool.h"

void* pth_func(void *args)
{
    thread_pool_t *p_manager = (thread_pool_t *)args; 
    pthread_t tid = pthread_self();

    printf("INFO : thread %ld create\n", tid);
    usleep(500);

    while(1)
    {
        printf("INFO : thread %ld waiting for job\n", tid);

        elem_t new_client = block_queue_pop(p_manager->block_queue);
        
        if(new_client.fd == -1)
        {
            pthread_exit(0);
        }

        printf("INFO : thread %ld do his job, fd = %d\n", tid, new_client.fd);

        send_file(new_client.fd);
        
        printf("INFO : thread %ld finish his job, fd = %d\n", tid, new_client.fd);

    }
}

thread_pool_t* thread_pool_init(int thread_num)
{
    thread_pool_t *p_manager = (thread_pool_t *)calloc(1, sizeof(thread_pool_t));
    if(p_manager == NULL)
    {
        error(-1, errno, "thread_pool calloc failed\n");
    }

    p_manager->pthid = (pthread_t *)calloc(thread_num, sizeof(pthread_t));
    if(p_manager->pthid == NULL)
    {
        error(-1, errno, "thread_pool pthid calloc failed\n");
    }

    p_manager->thread_num = thread_num;

    p_manager->block_queue = block_queue_create();

    for(int i = 0; i < thread_num; i++)
    {
        pthread_create(p_manager->pthid + i, NULL, pth_func, (void *)p_manager);
    }

    return p_manager;
}

void distribute_task(thread_pool_t *p_manager, elem_t new_client)
{
    block_queue_push(p_manager->block_queue, new_client);
}
