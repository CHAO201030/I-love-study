#include"bitmap.h"

BitMap* bitmap_create(size_t bits)
{
	BitMap* map = (BitMap*)malloc(sizeof(BitMap));
	if (map == NULL)
	{
		printf("Bitmap create failed, malloc failed\n");
		exit(-1);
	}

	map->bits = bits;

	size_t bytes = bits / 8;
	uint32_t* temp = (uint32_t*)calloc(1, bytes);
	if (temp == NULL)
	{
		printf("Bitmap create failed, calloc failed\n");
		exit(-1);
	}

	map->array = temp;

	return map;
}

void bitmap_destroy(BitMap* bm)
{
	if (bm == NULL)
	{
		printf("Bitmao destroy failed, map is empty\n");
		return;
	}

	free(bm->array);
	free(bm);
}

void bitmap_set(BitMap* bm, size_t n)
{
	if (bm == NULL)
	{
		printf("Bitmap set failed, map is empty\n");
		return;
	}

	unsigned int row_index = n / 32;	// arr[row_idx]
	unsigned int bit_index = n % 32;	// arr[row_idx]] | (0x01 << bit_idx)

	bm->array[row_index] |= (0x1u << bit_index);
}

void bitmap_unset(BitMap* bm, size_t n)
{
	if (bm == NULL)
	{
		printf("Bitmap unset failed, map is empty\n");
		return;
	}

	unsigned int row_index = n / 32;	// arr[row_idx]
	unsigned int bit_index = n % 32;	// arr[row_idx]] | (0x01 << bit_idx)

	bm->array[row_index] ^= (0x1u << bit_index);
}

bool bitmap_isset(BitMap* bm, size_t n)
{
	if (bm == NULL)
	{
		printf("Bitmap is set failed, map is empty\n");
		return false;
	}

	unsigned int row_index = n / 32;	// arr[row_idx]
	unsigned int bit_index = n % 32;	// arr[row_idx]] | (0x01 << bit_idx)
	unsigned int temp = bm->array[row_index];
	
	temp &= (0x1u << bit_index);
	
	return temp ? true : false;
}

void bitmap_clear(BitMap* bm)
{
	if (bm == NULL)
	{
		printf("Bitmap clear failed, map is empty\n");
		return;
	}

	for (int i = 0; i < MAX_CAPACITY_BITS / 32; i++)
	{
		bm->array[i] = 0;
	}
}