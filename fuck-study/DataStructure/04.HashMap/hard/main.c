#include"hashmap.h"

int main()
{
	HashMap* map = hashmap_create();

	hashmap_put(map, "hello", "world");
	hashmap_put(map, "C", "Linux");
	hashmap_put(map, "C++", "Python");
	hashmap_put(map, "Numpy", "Pandas");
	hashmap_put(map, "Java", "JVM");
	hashmap_put(map, "HTML", "5");
	hashmap_put(map, "sklearn", "Pytorch");
	print_hashmap(map);
	hashmap_put(map, "CHAO", "666");

	print_hashmap(map);
	hashmap_delete(map, "hello");
	hashmap_delete(map, "C");
	hashmap_delete(map, "C++");
	hashmap_delete(map, "Numpy");
	print_hashmap(map);

	hashmap_delete(map, "Java");
	hashmap_delete(map, "HTML");
	hashmap_delete(map, "sklearn");
	hashmap_delete(map, "CHAO");
	print_hashmap(map);

	printf("Hashmap get: %s\n", hashmap_get(map, "C"));
	printf("Hashmap get: %s\n", hashmap_get(map, "A"));

	hashmap_destroy(map);

	return 0;
}