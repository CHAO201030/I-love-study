#include"hash.h"

int main()
{
	HashMap* map = create_hashmap();

	int a[] = { 12,48,25,37,15,16,29,67,56,22,34,47 };
	for (int i = 0; i < 12; i++)
	{
		add_node(map, a[i]);
	}

	print_hash_map(map);

	add_node(map, 24);
	add_node(map, 24);

	print_hash_map(map);

	printf("This Data %s in Hash Map\n", find_by_val(map, 24) ? "Is" : "Is Not");

	del_node(map, 24);

	print_hash_map(map);

	for (int i = 0; i < 12; i++)
	{
		del_node(map, a[i]);
	}

	print_hash_map(map);

	return 0;
}