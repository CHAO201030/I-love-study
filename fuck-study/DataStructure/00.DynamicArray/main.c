#include"vector.h"

int main()
{
	Vector* v = vector_create();

	for (int i = 1; i < 11; i++)
	{
		push_back(v, i);
	}
	push_back(v, 11);
	print_vector(v);

	printf("pop back: %d\n", pop_back(v));
	printf("pop back: %d\n", pop_back(v));
	printf("pop back: %d\n", pop_back(v));
	print_vector(v);

	vector_destory(v);

	return 0;
}