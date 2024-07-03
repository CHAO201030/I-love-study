#include"bitmap.h"

int main()
{
	BitMap* map = bitmap_create(100);
	//bitmap_set(map, 9);
	//bitmap_set(map, 5);
	//bitmap_set(map, 2);
	//bitmap_set(map, 7);
	//bitmap_set(map, 120);
	//bitmap_set(map, 128);
	//bitmap_unset(map, 120);
	//bitmap_unset(map, 2);
	//printf("Is set ? %s\n", bitmap_isset(map, 5) ? "True" : "False");
	//printf("Is set ? %s\n", bitmap_isset(map, 120) ? "True" : "False");
	//bitmap_clear(map);

	bitmap_destroy(map);
	return 0;
}