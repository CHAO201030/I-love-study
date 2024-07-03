#include"list.h"

void print_list(const List* list)
{
	if (list->size == 0)
	{
		printf("List is empty\n");
		return;
	}
	else
	{
		Node* pCur = list->head;
		while (pCur)
		{
			printf("%3c ->", pCur->val);
			pCur = pCur->next;
		}
		printf(" NULL\n");
	}
}

List* create_list()
{
	List* list = (List*)calloc(1, sizeof(List));
	if (list == NULL)
	{
		printf("List create failed, calloc failed\n");
		exit(-1);
	}

	return list;
}

void destroy_list(List* list)
{
	if (list->size == 0)
	{
		printf("List is empty\n");
	}
	else
	{
		Node* pCur = list->head;
		while (list->size)
		{
			list->head = list->head->next;
			free(pCur);
			pCur = list->head;
			list->size--;
		}
		list->tail = NULL;
	}
}

void add_before_head(List* list, E val)
{
	Node* pNew = (Node*)calloc(1, sizeof(Node));
	if (pNew == NULL)
	{
		printf("List add Before head failed, calloc failed\n");
		exit(-1);
	}

	pNew->val = val;
	pNew->next = NULL;

	if (list->head == NULL)
	{
		list->head = pNew;
		list->tail = pNew;
	}
	else
	{
		pNew->next = list->head;
		list->head = pNew;
	}
	list->size++;
}

void add_behind_tail(List* list, E val)
{
	Node* pNew = (Node*)calloc(1, sizeof(Node));
	if (pNew == NULL)
	{
		printf("List add behind tail failed, calloc failed\n");
		exit(-1);
	}

	pNew->val = val;
	pNew->next = NULL;

	if (list->tail == NULL)
	{
		list->tail = pNew;
		list->head = pNew;
	}
	else
	{
		list->tail->next = pNew;
		list->tail = pNew;
	}
	list->size++;
}

void add_node(List* list, int idx, E val)
{
	if (idx > list->size)
	{
		printf("Add node by index failed, please input correct index"
			"[ %d - %d ]\n", 0, list->size);
		return;
	}
	else if (idx == list->size)
	{
		add_behind_tail(list, val);
	}
	else if (idx == 0)
	{
		add_before_head(list, val);
	}
	else
	{
		Node* pNew = (Node*)calloc(1, sizeof(Node));
		pNew->val = val;

		Node* pCur = list->head;
		
		while (idx > 1)
		{
			pCur = pCur->next;
			idx--;
		}

		pNew->next = pCur->next;
		pCur->next = pNew;
		list->size++;
	}
}

void delete_node(List* list, E val)
{
	if (list->head == NULL)
	{
		printf("Delet node failed, list is empty\n");
		return;
	}
	else
	{
		Node* pCur = list->head;
		Node* pPre = NULL;

		while (pCur)
		{
			if (pCur->val == val)
			{
				break;
			}
			pPre = pCur;
			pCur = pCur->next;
		}

		if (pCur == NULL)
		{
			printf("Delet node failed, no such node\n");
			return;
		}

		if (pCur == list->head)
		{
			// 被删结点为头指针指向的结点
			list->head = pCur->next;
			free(pCur);
			list->size--;
			if (list->size == 0)
			{
				// 删除的是链表中最后一个结点
				list->tail = NULL;
			}
			return;
		}

		pPre->next = pCur->next;

		if (pCur == list->tail)
		{
			list->tail = pPre;
		}

		free(pCur);
		list->size--;
	}
}

Node* find_by_index(const List* list, int idx)
{
	if (idx >= list->size)
	{
		printf("Find by index failed\n");
		return NULL;
	}
	else
	{
		Node* pCur = list->head;
		while (idx)
		{
			pCur = pCur->next;
			idx--;
		}
		return pCur;
	}
}

Node* search_for_value(const List* list, E val)
{
	if (list->head == NULL)
	{
		printf("Search For Vavlue Failed: List Is Empty\n");
		return NULL;
	}
	else
	{
		Node* pCur = list->head;
		while (pCur)
		{
			if (pCur->val == val)
			{
				return pCur;
			}
			pCur = pCur->next;
		}
		printf("Search For Vavlue Failed: No Such Node\n");
		return NULL;
	}
}