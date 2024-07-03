#include"list.h"

int main()
{
	Node* p = NULL;
	List* list = create_list();

	add_before_head(list, 'b');
	add_behind_tail(list, 'd');

	add_node(list, 0, 'a');
	add_node(list, 2, 'c');
	add_node(list, 4, 'e');

	print_list(list);

	//p = find_by_index(list, 8);
	p = search_for_value(list, 'f');

	//destroy_list(list);

	delete_node(list, 'g');
	delete_node(list, 'e');
	delete_node(list, 'b');

	print_list(list);

	delete_node(list, 'c');
	delete_node(list, 'd');
	delete_node(list, 'a');

	print_list(list);

	return 0;
}