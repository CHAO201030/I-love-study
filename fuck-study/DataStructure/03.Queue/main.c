#include"queue.h"

int main()
{
	Queue* q = queue_create();

	printf("Queue is empty? %s\n", queue_empty(q) ? "empty" : "false");

	for (int i = 0; i < 10; i++)
	{
		queue_push(q, i);
	}

	printf("%d\n", queue_pop(q));
	printf("%d\n", queue_pop(q));
	printf("%d\n", queue_pop(q));

	queue_push(q, 10);
	queue_push(q, 11);
	queue_push(q, 12);
	queue_push(q, 13);

	printf("%d\n", queue_pop(q));

	printf("%d\n", queue_peek(q));

	int count = q->size;
	for (int i = 0; i < count; i++)
	{
		printf("%2d ", queue_pop(q));
	}

	queue_destroy(q);

	return 0;
}