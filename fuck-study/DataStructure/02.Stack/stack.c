#include"stack.h"

Stack* stack_create(void)
{
	Stack* s = (Stack*)calloc(1, sizeof(Stack));
	if (s == NULL)
	{
		printf("Stack Create Failed\n");
		exit(-1);
	}

	s->size = 0;
	s->top = NULL;

	return s;
}

void stack_push(Stack* s, E val)
{
	Node* pNew = (Node*)calloc(1, sizeof(Node));
	if (pNew == NULL)
	{
		printf("Stack Push Failed\n");
		exit(-1);
	}

	pNew->val = val;
	pNew->next = NULL;

	if (s->top == NULL)
	{
		s->top = pNew;
	}
	else
	{
		pNew->next = s->top;
		s->top = pNew;
	}
	s->size++;
}

E stack_pop(Stack* s)
{
	if (s->top == NULL)
	{
		printf("Stack Pop Failed\n");
		return STACK_POP_FAILED;
	}
	else
	{
		E temp = s->top->val;
		Node* pTop = s->top;

		s->top = s->top->next;
		s->size--;

		free(pTop);

		return temp;
	}
}

E stack_peek(Stack* s)
{
	if (s->top == NULL)
	{
		printf("Stack Peek Failed\n");
		return STACK_PEEK_FAILED;
	}
	else
	{
		return s->top->val;
	}
}

void stack_destory(Stack* s)
{
	if (s->top == NULL)
	{
		return;
	}
	else
	{
		while (s->top)
		{
			stack_pop(s);
		}
	}
}

bool stack_empty(Stack* s)
{
	return s->size == 0 ? true : false;
}