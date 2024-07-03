#include"BST.h"
#include"queue.h"

Queue* queue_create()
{
	Queue* q = calloc(1, sizeof(Queue));
	if (q == NULL)
	{
		printf("Queue create failed, calloc failed\n");
		return NULL;
	}
	q->capacity = MAX_CAPACITY;

	return q;
}

void queue_destroy(Queue* q)
{
	free(q->elements);
	free(q);
}

void queue_expansion(Queue* q)
{
	int new_capacity = q->capacity + MAX_CAPACITY;
	E* temp = (E*)malloc(new_capacity * sizeof(E));
	if (temp == NULL)
	{
		printf("Queue expansion failed, realloc failed\n");
		exit(-1);
	}

	for (int i = 0; i < q->size; i++)
	{
		temp[i] = q->elements[(q->front + i) % q->capacity];
	}

	free(q->elements);

	q->elements = temp;
	q->front = 0;
	q->rear = q->size;
	q->capacity = new_capacity;
}

void queue_push(Queue* q, E val)
{
	if (q->size == 0)
	{
		E* temp = (E*)calloc(MAX_CAPACITY, sizeof(E));
		if (temp == NULL)
		{
			printf("Queue push failed, queue->elements calloc failed\n");
			return;
		}
		q->elements = temp;
		q->rear++;
		q->size++;
		q->elements[q->front] = val;
	}
	else
	{
		if (q->size >= q->capacity)
		{
			// expansion
			queue_expansion(q);
		}
		q->elements[q->rear] = val;
		q->rear = (q->rear + 1) % q->capacity;
		q->size++;
	}
}

E queue_pop(Queue* q)
{
	if (q->size == 0)
	{
		printf("Queue pop failed, queue is empty\n");
		exit(-1);
	}
	else
	{
		E temp = q->elements[q->front];
		q->front = (q->front + 1) % q->capacity;
		q->size--;
		return temp;
	}
}

E queue_peek(Queue* q)
{
	if (q->size == 0)
	{
		printf("Queue peek failed, queue is empty\n");
		exit(-1);
	}
	return q->elements[q->front];
}

bool queue_empty(Queue* q)
{
	return q->size == 0 ? true : false;
}