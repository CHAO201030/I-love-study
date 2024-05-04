#include"bst.h"
#include"queue.h"


int main()
{
	TreeNode* test = NULL;
	BST* tree = bst_create();
	bst_insert(tree, 3);
	bst_insert(tree, 2);
	bst_insert(tree, 4);
	bst_insert(tree, 42);
	bst_insert(tree, 13);
	bst_insert(tree, 57);

	test = bst_search(tree, 13);
	if (test)printf("%d\n", test->key);
	//test = bst_search(tree, 88);
	//if (test)printf("%d\n", test->key);
	
	bst_preorder(tree);
	bst_inorder(tree);
	bst_postorder(tree);
	bst_levelorder(tree);

	bst_delete(tree, 3);
	bst_delete(tree, 2);
	bst_delete(tree, 4);

	bst_levelorder(tree);
	bst_destroy(tree);
	tree = NULL;

	return 0;
}