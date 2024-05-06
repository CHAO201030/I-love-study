#include"bitmap.h"

BitMap* bitmap_create(size_t bits)
{
	BitMap* map = (BitMap*)malloc(1 * sizeof(BitMap));
	if (map == NULL)
	{
		printf("Bitmap create failed, malloc failed\n");
		exit(-1);
	}
	
	map->array = (word*)calloc(BITMAP_SIZE(bits), sizeof(word));
	if (map->array == NULL)
	{
		printf("Bitmap create failed, calloc failed\n");
		exit(-1);
	}

	map->bits = bits;

	return map;
}

void bitmap_destroy(BitMap* bm)
{
	free(bm->array);
	free(bm);
}

void array_expansion(BitMap* bm, size_t bits)
{
	word* temp = (word*)realloc(bm->array, BITMAP_SIZE(bits) * sizeof(word));
	if (temp == NULL)
	{
		printf("Bitmap->array expansion failed, calloc failed\n");
		exit(-1);
	}

	int Bytes = (BITMAP_SIZE(bits) - BITMAP_SIZE(bm->bits)) * sizeof(word);
	memset(bm->array + BITMAP_SIZE(bm->bits), 0, Bytes);
	bm->bits = bits;
}

void bitmap_set(BitMap* bm, size_t n)
{
	if (bm == NULL || bm->array == NULL)
	{
		printf("Bitmap set failed, bm or bm->array is not initialized\n");
		exit(-1);
	}

	if (BITMAP_SIZE(n + 1) > BITMAP_SIZE(bm->bits))
	{
		array_expansion(bm, n + 1);
	}

	size_t row_idx = n >> BITMAP_SHIFT;
	size_t bit_idx = n & BITMAP_MASK;

	bm->array[row_idx] |= (0x1u << bit_idx);
}

void bitmap_unset(BitMap* bm, size_t n)
{
	if (n > bm->bits)
	{
		return;
	}
	size_t row_idx = n >> BITMAP_SHIFT;
	size_t bit_idx = n & BITMAP_MASK;

	bm->array[row_idx] &= ~(0x1u << bit_idx);
}

bool bitmap_isset(BitMap* bm, size_t n)
{
	if (n > bm->bits)
	{
		return false;
	}
	size_t row_idx = n >> BITMAP_SHIFT;
	size_t bit_idx = n & BITMAP_MASK;

	return bm->array[row_idx] & (0x1u << bit_idx);
}

void bitmap_clear(BitMap* bm)
{
	size_t size = BITMAP_SIZE(bm->bits);
	memset(bm->array, 0, size * sizeof(word));
}