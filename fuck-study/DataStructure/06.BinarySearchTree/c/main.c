#include"BST.h"
#include"queue.h"

int main()
{
	BST* tree = bst_create();
	bst_insert(tree, 9);
	bst_insert(tree, 5);
	//bst_insert(tree, 3);
	//bst_insert(tree, 42);
	//bst_insert(tree, 13);
	//bst_insert(tree, 57);

	bst_preorder(tree);
	bst_inorder(tree);
	bst_postorder(tree);
	bst_levelorder(tree);
	printf("\n");
	bst_levelorder2(tree);
	printf("\n\n");

	bst_delete(tree, 9);
	bst_levelorder2(tree);

	return 0;
}