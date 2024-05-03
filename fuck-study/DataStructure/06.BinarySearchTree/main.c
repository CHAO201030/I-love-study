#include"bst.h"


int main()
{
	TreeNode* test = NULL;
	BST* tree = bst_create();
	bst_insert(tree, 9);
	bst_insert(tree, 5);
	bst_insert(tree, 3);
	bst_insert(tree, 42);
	bst_insert(tree, 13);
	bst_insert(tree, 57);

	test = bst_search(tree, 13);
	if (test)printf("%d\n", test->key);
	test = bst_search(tree, 10086);
	if (test)printf("%d\n", test->key);
	bst_inorder(tree);


	bst_delete(tree, 4);

	return 0;
}