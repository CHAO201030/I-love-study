#include"hashmap.h"

/* murmurhash2 */
static uint32_t hash(const void* key, int len, uint32_t seed) {
	const uint32_t m = 0x5bd1e995;
	const int r = 24;
	uint32_t h = seed ^ len;
	const unsigned char* data = (const unsigned char*)key;
	while (len >= 4)
	{
		uint32_t k = *(uint32_t*)data;
		k *= m;
		k ^= k >> r;
		k *= m;
		h *= m;
		h ^= k;
		data += 4;
		len -= 4;
	}
	switch (len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
		h *= m;
	};
	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

HashMap* hashmap_create()
{
	HashMap* map = (HashMap*)calloc(1, sizeof(HashMap));
	if (map == NULL)
	{
		printf("Hashmap create failed, calloc map failed\n");
		exit(-1);
	}

	map->table = (Node**)calloc(DEFAULT_CAPACITY, sizeof(Node*));
	if (map->table == NULL)
	{
		printf("Hashmap create failed, calloc map->table failed\n");
		exit(-1);
	}

	map->capacity = DEFAULT_CAPACITY;
	map->hashseed = time(NULL);

	return map;
}

void hashmap_destroy(HashMap* map)
{
	for (int i = 0; i < map->capacity; i++)
	{
		Node* pCur = map->table[i];
		Node* pNext = NULL;
		while (pCur)
		{
			pNext = pCur->next;
			free(pCur);
			pCur = pNext;
		}
	}
	free(map->table);
	free(map);
}

void table_expansion(HashMap* map)
{
	int new_capacity = map->capacity << 1;
	int new_seed = time(NULL);
	Node** temp = (Node*)calloc(new_capacity, sizeof(Node*));
	if (temp == NULL)
	{
		printf("Hashmap expansion failed, calloc failed\n");
		exit(-1);
	}
	
	for (int i = 0; i < map->capacity; i++)
	{
		// 重新映射
		// 遍历原表，找节点的key，对key进行新的hash得到newidx
		if (map->table[i])
		{
			Node* pCur = map->table[i];
			Node* pNext = NULL;
			while (pCur)
			{
				pNext = pCur->next;
				int new_index = hash(pCur->key, strlen(pCur->key), new_seed) % new_capacity;
				if (temp[new_index] == NULL)
				{
					temp[new_index] = pCur;
					pCur->next = NULL;
				}
				else
				{
					pCur->next = temp[new_index];
					temp[new_index] = pCur;
				}
				pCur = pNext;
			}
		}
	}

	map->capacity = new_capacity;
	map->hashseed = new_seed;
	free(map->table);
	map->table = temp;
}

V hashmap_put(HashMap* map, K key, V val)
{
	if (map == NULL || map->table == NULL)
	{
		printf("Hashmap put failed, map or map->table is not initialized\n");
		exit(-1);
	}

	int index = hash(key, strlen(key), map->hashseed) % map->capacity;
	Node* pCur = map->table[index];

	while (pCur)
	{
		if (strcmp(pCur->key, key) == 0)
		{
			V old_val = pCur->val;
			pCur->val = val;

			return old_val;
		}
		pCur = pCur->next;
	}

	float load = (float)map->size / map->capacity;
	if (load > DEFAULT_LOAD_FACTOR)
	{
		//扩容
		table_expansion(map);
		index = hash(key, strlen(key), map->hashseed) % map->capacity;
	}

	Node* pNew = (Node*)malloc(sizeof(Node));
	if (pNew == NULL)
	{
		printf("Hashmap put failied, malloc failed\n");
		return NULL;
	}

	pNew->key = key;
	pNew->val = val;
	pNew->next = map->table[index];

	map->table[index] = pNew;
	map->size++;

	return NULL;
}

V hashmap_get(HashMap* map, K key)
{
	if (map == NULL || map->table == NULL)
	{
		printf("Hashmap put failed, map or map->table is not initialized\n");
		exit(-1);
	}

	int index = hash(key, strlen(key), map->hashseed) % map->capacity;
	Node* pCur = map->table[index];

	while (pCur)
	{
		if (strcmp(pCur->key, key) == 0)
		{
			return pCur->val;
		}
		pCur = pCur->next;
	}

	return NULL;
}

void hashmap_delete(HashMap* map, K key)
{
	if (map == NULL || map->table == NULL)
	{
		printf("Hashmap put failed, map or map->table is not initialized\n");
		exit(-1);
	}

	int index = hash(key, strlen(key), map->hashseed) % map->capacity;

	if (map->table[index] == NULL)
	{
		printf("No such node\n");

		return;
	}
	else
	{
		Node* pCur = map->table[index];

		if (strcmp(pCur->key, key) == 0)
		{
			map->table[index] = map->table[index]->next;
			map->size--;
			free(pCur);

			return;
		}
		
		Node* pPre = map->table[index];
		while (pCur)
		{
			if (strcmp(pCur->key, key) == 0)
			{
				pPre->next = pCur->next;
				map->size--;
				free(pCur);

				return;
			}
			pPre = pCur;
			pCur = pCur->next;
		}
		printf("No such node\n");

		return;
	}
}

void print_hashmap(const HashMap* map)
{
	for (int i = 0; i < map->capacity; i++)
	{
		printf("table[%2d]: ", i);
		Node* pCur = map->table[i];
		if (pCur == NULL)
		{
			printf("NULL\n");
			continue;
		}

		while (pCur)
		{
			printf("%10s ->",pCur->val);
			pCur = pCur->next;
		}
		printf("NULL\n");
	}
	printf("\n");
}