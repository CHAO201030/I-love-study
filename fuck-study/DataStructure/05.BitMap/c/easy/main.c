#include"bitmap.h"


int main()
{
	// Bitmap : 4096 bit, 4096个数字 --> 128 B
	// int    : 16384 B , 4096个数字
	BitMap* map = bitmap_create((size_t)MAX_CAPACITY_BITS);
	unsigned int num = 0;
	
	//printf("Input a num range of [0 ~ 4095] : ");
	//scanf("%u", &num);
	//if (num > 4095 || num < 0)
	//{
	//	printf("Error num\n");
	//	exit(-1);
	//}
	
	bitmap_set(map, 24u);
	bitmap_set(map, 63u);
	bitmap_set(map, 0u);
	bitmap_set(map, 4095u);

	printf("%4u is in BitMap ? %s\n", 24u, bitmap_isset(map, 24u) ? "True" : "False");
	printf("%4u is in BitMap ? %s\n", 63u, bitmap_isset(map, 63u) ? "True" : "False");
	printf("%4u is in BitMap ? %s\n", 0u, bitmap_isset(map, 0u) ? "True" : "False");
	printf("%4u is in BitMap ? %s\n", 4095u, bitmap_isset(map, 4095u) ? "True" : "False");

	bitmap_unset(map, 24u);
	printf("%4u is in BitMap ? %s\n", 24u, bitmap_isset(map, 24u) ? "True" : "False");

	bitmap_clear(map);
	printf("%4u is in BitMap ? %s\n", 4095u, bitmap_isset(map, 4095u) ? "True" : "False");

	bitmap_destroy(map);
	map = NULL;

	return 0;
}