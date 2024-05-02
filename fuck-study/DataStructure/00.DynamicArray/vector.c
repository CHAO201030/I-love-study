#include"vector.h"

Vector* vector_create()
{
	Vector* v = (Vector*)calloc(1, sizeof(Vector));
	if (v == NULL)
	{
		printf("Vector create failed, calloc failed\n");
		exit(-1);
	}
	v->capacity = MAX_CAPACITY;
	return v;
}

void vector_destory(Vector* v)
{
	free(v->elements);
	free(v);
}

void print_vector(const Vector* v)
{
	if (v->size == 0)
	{
		printf("Vector is empty\n");
	}
	else
	{
		for (int i = 0; i < v->size; i++)
		{
			printf("%3d ", v->elements[i]);
		}
		printf("\n");
	}
}

void vector_expansion(Vector* v)
{
	int new_capacity = v->capacity + MAX_CAPACITY;
	E* temp = (E*)realloc(v->elements, new_capacity * sizeof(E));
	if (temp == NULL)
	{
		printf("Vector expansion failed, realloc failed\n");
		exit(-1);
	}
	v->elements = temp;
	v->capacity = new_capacity;
}

void vector_contraction(Vector* v)
{
	int new_capacity = v->capacity - MAX_CAPACITY;
	E* temp = (E*)realloc(v->elements, new_capacity * sizeof(E));
	if (temp == NULL)
	{
		printf("Vector contraction failed, realloc failed\n");
		exit(-1);
	}
	v->elements = temp;
	v->capacity = new_capacity;
}

void push_back(Vector* v, E data)
{
	if (v->size == 0)
	{	
		E* temp = (E*)calloc(v->capacity, sizeof(E));
		if (temp == NULL)
		{
			printf("Push back failed, calloc failed\n");
			exit(-1);
		}
		v->elements = temp;
	}
	else
	{
		if (v->size >= v->capacity)
		{
			vector_expansion(v);
		}
	}
	v->elements[v->size++] = data;
}

void push_front(Vector* v, E data)
{
	if (v->size == 0)
	{
		E* temp = (E*)calloc(v->capacity, sizeof(E));
		if (temp == NULL)
		{
			printf("Push front failed, calloc failed\n");
			exit(-1);
		}
		v->elements = temp;
	}
	else
	{
		if (v->size >= v->capacity)
		{
			vector_expansion(v);
		}

		for (int i = v->size; i > 0; i--)
		{
			v->elements[i] = v->elements[i - 1];
		}
	}
	v->elements[0] = data;
	v->size++;
}

E pop_back(Vector* v)
{
	if (v->size == 0)
	{
		printf("Pop back failed, vector is empty\n");
		exit(-1);
	}
	else
	{
		if (v->size <= v->capacity - MAX_CAPACITY)
		{
			vector_contraction(v);
		}

		return v->elements[--v->size];
	}
}

E pop_front(Vector* v)
{
	if (v->size == 0)
	{
		printf("Pop front failed, vector is empty\n");
		exit(-1);
	}
	else
	{
		if (v->size <= v->capacity - MAX_CAPACITY)
		{
			vector_contraction(v);
		}

		int ret = v->elements[0];

		for(int i = 0; i < v->size; i++)
		{
			v->elements[i] = v->elements[i + 1];
		}
		v->size--;

		return ret;
	}
}