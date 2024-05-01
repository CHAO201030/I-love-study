#include"hash.h"


HashMap* create_hashmap()
{
	HashMap* map = (HashMap*)calloc(1, sizeof(HashMap));
	
	return map;
}

int hash(int data)
{
	return data % MAX_SIZE;
}

void add_node(HashMap* map, int data)
{
	int key = hash(data);
	Node* pCur = map->table[key];
	Node* pPre = NULL;

	Node* pNew = (Node*)malloc(sizeof(Node));
	if (pNew == NULL)
	{
		printf("Hash Map add node failed, malloc failed\n");
		return;
	}

	pNew->data = data;
	pNew->next = NULL;

	if (pCur == NULL)
	{
		// 散列后为第一个插入的结点
		map->table[key] = pNew;
	}
	else
	{
		// 散列后发生冲突
		while (pCur)
		{
			if (pCur->data == data)
			{
				printf("Repeated node %d\n", data);
				free(pNew);
				return;
			}
			pPre = pCur;
			pCur = pCur->next;
		}
		pPre->next = pNew;
	}
	map->size++;
}

bool find_by_val(const HashMap* map, int val)
{
	if (map->size == 0)
	{
		printf("Hash map is empty\n");
		return false;
	}
	else
	{
		int key = hash(val);
		if (map->table[key] == NULL)
		{
			printf("No such node\n");
			return false;
		}
		else
		{
			Node* pCur = map->table[key];
			while (pCur)
			{
				if (pCur->data == val)
				{
					printf("Find success\n");
					return true;
				}
				pCur = pCur->next;
			}
			return false;
		}
	}
}

void del_node(HashMap* map, int data)
{
	if (map->size == 0)
	{
		printf("Hash map is empty\n");
		return;
	}
	else
	{
		int key = hash(data);
		
		// 这个链是空链
		if (map->table[key] == NULL)
		{
			printf("No such node\n");
			return;
		}
		else
		{
			Node* pCur = map->table[key];
			Node* pPre = NULL;

			// 删除的是这个链中第一个结点
			if (pCur->data == data)
			{
				map->table[key] = pCur->next;
				map->size--;
				free(pCur);
				return;
			}

			while (pCur)
			{
				if (pCur->data == data)
				{
					break;
				}
				pPre = pCur;
				pCur = pCur->next;
			}
			//48->24->12->NULL
			if (pCur == NULL)
			{
				printf("No such node\n");
				return;
			}
			else
			{
				pPre->next = pCur->next;
				map->size--;
				free(pCur);
				return;
			}
		}
	}
}

void print_hash_map(const HashMap* map)
{
	if (map->size == 0)
	{
		printf("Hash map is empty\n");
		return;
	}
	else
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			printf("Node %2d : ", i);
			if (map->table[i] == NULL)
			{
				printf("  NULL\n");
			}
			else
			{
				Node* pCur = map->table[i];
				while (pCur)
				{
					printf("%4d ->", pCur->data);
					pCur = pCur->next;
				}
				printf(" NULL\n");
			}
		}
	}
	printf("\n");
}
