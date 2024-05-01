#include"stack.h"

int main()
{
	E pop;
	E peek;
	bool empty;

	Stack* s = stack_create();
	
	for (E i = 1; i <= 5; i++)
	{
		stack_push(s, i);
	}
	
	pop = stack_pop(s);
	if (pop == STACK_POP_FAILED)
	{
		return -1;
	}
	printf("Stack Pop is %d\n", pop);

	peek = stack_peek(s);
	if (peek == STACK_PEEK_FAILED)
	{
		return -1;
	}
	printf("Stack Peek is %d\n", peek);

	empty = stack_empty(s);
	printf("Stack is empty ? %s\n", empty ? "True" : "False");

	stack_destory(s);
	
	empty = stack_empty(s);
	printf("Stack is empty ? %s\n", empty ? "True" : "False");

	return 0;
}