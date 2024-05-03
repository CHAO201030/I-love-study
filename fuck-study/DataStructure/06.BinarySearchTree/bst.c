#include"bst.h"

BST* bst_create()
{
	BST* tree = (BST*)calloc(1, sizeof(BST));
	if (tree == NULL)
	{
		printf("BST create failed, calloc failed\n");
		exit(-1);
	}

	return tree;
}

TreeNode* bst_search(BST* tree, K key)
{
	if (tree == NULL || tree->root == NULL)
	{
		printf("BST search failed, BST is empty or not initialized\n");
		return NULL;
	}
	else
	{
		TreeNode* pCur = tree->root;
		while (pCur)
		{
			if (pCur->key == key)
			{
				return pCur;
			}
			pCur = key > pCur->key ? pCur->right : pCur->left;
		}
		return NULL;
	}
}

void bst_destroy(BST* tree)
{

}

void bst_insert(BST* tree, K key)
{
	if (tree == NULL)
	{
		printf("BST insert failed, BST is NULL\n");
		exit(-1);
	}
	else
	{
		TreeNode* pNew = (TreeNode*)calloc(1, sizeof(TreeNode));
		if (pNew == NULL)
		{
			printf("BST insert failed, malloc failed\n");
			exit(-1);
		}

		pNew->key = key;

		if (tree->root == NULL)
		{
			tree->root = pNew;
			return;
		}
		else
		{
			// 根据 key 值找位置 new_key > cur_key,向右子树走，不然向左子树走
			TreeNode* pCur = tree->root;
			TreeNode* pPre = NULL;
			while (pCur)
			{
				if (pCur->key == key)
				{
					printf("BST insert failed, data already in BST\n\n");
					free(pNew);
					return;
				}
				pPre = pCur;
				// key大向右走，key小向左走
				pCur = key > pCur->key ? pCur->right : pCur->left;
			}

			// pNew小插入到左孩子，pNew大插入到右孩子
			if (pPre->key > pNew->key)
			{
				pPre->left = pNew;
				return;
			}
			pPre->right = pNew;
		}
	}
}

void bst_delete(BST* tree, K key)
{
	if (tree == NULL || tree->root == NULL)
	{
		printf("BST search failed, BST is empty or not initialized\n");
		return;
	}
	else
	{
		TreeNode* pCur = tree->root;
		TreeNode* pParent = NULL;

		// 找到要删除的节点
		while (pCur)
		{
			if (pCur->key == key)break;
			pParent = pCur;
			pCur = key > pCur->key ? pCur->right : pCur->left;

		}

		if (pCur == NULL)
		{
			printf("BST delete node failed, no such node\n");
			return;
		}

		// case a : 被删除节点没有孩子，直接删除，父节点指针改为NULL
		if (pCur->left == NULL && pCur->right == NULL)
		{

		}

		// case b : 被删除节点有两个孩子，找他中序遍历的直接前驱或后继代替他，转化为case a
		if (pCur->left && pCur->right)
		{
			// 找中序直接前驱节点

			// 找中序直接后继节点

		}

		// case c : 被删除节点有一个孩子，让父节点指针指向其孩子
		if (pCur->left || pCur->right)
		{

		}
	}
}

void pre_order(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		printf("%3d ", node->key);
		pre_order(node->left);
		pre_order(node->right);
	}
}

void bst_preorder(BST* tree)
{
	pre_order(tree->root);
	printf("\n");
}

void in_order(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		in_order(node->left);
		printf("%3d ", node->key);
		in_order(node->right);
	}
}

void bst_inorder(BST* tree)
{
	in_order(tree->root);
	printf("\n");
}

void post_order(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		post_order(node->left);
		post_order(node->right);
		printf("%3d ", node->key);
	}

}

void bst_postorder(BST* tree)
{
	post_order(tree->root);
	printf("\n");
}

void bst_levelorder(BST* tree)
{

}