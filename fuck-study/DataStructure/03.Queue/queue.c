#include"queue.h"

Queue* queue_create()
{
	Queue* q = (Queue*)calloc(1, sizeof(Queue));
	if (q == NULL)
	{
		printf("Queue Create Failed\n");
		exit(-1);
	}
	else
	{
		q->capacity = QUEUE_CAPACITY;
		q->size = 0;
		q->elements = (E*)calloc(QUEUE_CAPACITY + 1, sizeof(E));
		// 队头队尾相等时为空,队尾指向下一个元素的插入位置
		q->front = 0;
		q->rear = 0;
	}

	return q;
}

void queue_destory(Queue* q)
{
	if (q->size == 0)
	{
		return;
	}
	else
	{
		while (q->size)
		{
			queue_pop(q);
		}
		q->front = 0;
		q->rear = 0;
		q->capacity = 0;
		free(q->elements);
		q->elements = NULL;
	}
}

void queue_push(Queue* q, E val)
{
	if (q->size == 0)
	{
		q->size++;
		q->elements[q->rear++] = val;
	}
	else if (q->size == QUEUE_CAPACITY)
	{
		// 扩容
		int new_capacity = q->capacity + QUEUE_CAPACITY + 1;

		E* temp = (E*)realloc(q->elements, new_capacity * sizeof(int));
		if (NULL == temp)
		{
			printf("Queue Expansion Failed\n");
			return;
		}
		// 扩容后的新空间清0
		for (int i = q->rear; i < new_capacity; i++)
		{
			temp[i] = 0;
		}

		q->capacity += QUEUE_CAPACITY;
		q->elements = temp;
		q->elements[q->rear] = val;
		q->size++;
		q->rear = (q->rear++) % (q->capacity + 1);
	}
	else
	{
		q->size++;
		q->elements[q->rear] = val;
		q->rear = (q->rear++) % (q->capacity + 1);
	}
}

E queue_pop(Queue* q)
{
	if (q->size == 0)
	{
		printf("Queue Pop Failed\n");
		return QUEUE_POP_FAILED;
	}
	else
	{
		E temp = q->elements[q->front];
		q->front = (q->front++) % (q->capacity + 1);
		q->size--;
		
		return temp;
	}
}

E queue_peek(Queue* q)
{
	if (q->size == 0)
	{
		printf("Queue Peek Failed\n");
		return QUEUE_PEEK_FAILED;
	}
	else
	{
		return q->elements[q->front];
	}
}

bool queue_empty(Queue* q)
{
	return q->size == 0 ? true : false;
}