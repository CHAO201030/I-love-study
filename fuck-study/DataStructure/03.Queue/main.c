#include"queue.h"

int main()
{
	E pop;
	E peek;
	bool empty;

	Queue* q = queue_create();
	for (E i = 1; i <= 4; i++)
	{
		queue_push(q, i);
	}
	queue_push(q, 5);

	pop = queue_pop(q);
	if (pop == QUEUE_POP_FAILED)
	{
		return -1;
	}
	printf("Queue Pop is %d\n", pop);

	peek = queue_peek(q);
	if (peek == QUEUE_PEEK_FAILED)
	{
		return -1;
	}
	printf("Queue Peek is %d\n", peek);

	empty = queue_empty(q);
	printf("Queue is empty ? %s\n", empty ? "True" : "False");

	queue_destory(q);

	empty = queue_empty(q);
	printf("Queue is empty ? %s\n", empty ? "True" : "False");
	
	return 0;
}