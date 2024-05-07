#include"BST.h"
#include"queue.h"

BST* bst_create(void)
{
	BST* tree = (BST*)calloc(1, sizeof(BST));
	if (tree == NULL)
	{
		printf("BST create failed, calloc failed\n");
		exit(-1);
	}

	return tree;
}

void destroy_node(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		destroy_node(node->left);
		destroy_node(node->right);
		free(node);
	}
}

void bst_destroy(BST* tree)
{
	if (tree->root == NULL)
	{
		return;
	}
	else
	{
		destroy_node(tree->root);
		free(tree);
	}
}

void bst_insert(BST* tree, K key)
{
	if (tree == NULL)
	{
		printf("BST insert failed, BST  not initialized\n");
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

void bst_delete(BST* tree, K key)
{
	if (tree == NULL || tree->root == NULL)
	{
		printf("BST delete failed, BST is empty or not initialized\n");
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

		// 没找到该节点
		if (pCur == NULL)
		{
			printf("BST delete node failed, no such node\n");
			return;
		}

		// case a : 被删除节点有两个孩子，找他中序遍历的直接前驱或后继代替他，转化为case b or c
		if (pCur->left && pCur->right)
		{
			/*

			// 找中序直接前驱节点 左的最右
			TreeNode* pPre = pCur->left;
			TreeNode* pPre_parent = pCur;

			// 找左子树的最右下节点
			while (pPre->right)
			{
				pPre_parent = pPre;
				pPre = pPre->right;
			}
			// 转化为 case b or c
			pCur->key = pPre->key;
			pCur = pPre;
			pParent = pPre_parent;

			*/

			// 找中序直接后继节点 右的最左
			TreeNode* pPost = pCur->right;
			TreeNode* pPost_parent = pCur;

			// 找右子树的最左下节点
			while (pPost->left)
			{
				pPost_parent = pPost;
				pPost = pPost->left;
			}

			// 转化为case b or c
			pCur->key = pPost->key;
			pCur = pPost;
			pParent = pPost_parent;
		}

		// case a : 被删除节点没有孩子，直接删除，父节点指针改为NULL
		if (pCur->left == NULL && pCur->right == NULL)
		{
			if (pParent == NULL)
			{
				// 删除的是根节点
				tree->root = NULL;
				free(pCur);
				return;
			}

			if (pParent->left == pCur)
			{
				pParent->left = NULL;
			}
			else
			{
				pParent->right = NULL;
			}

			free(pCur);
			return;
		}

		// case c : 被删除节点有一个孩子，让父节点指针指向其孩子
		if (pCur->left || pCur->right)
		{
			TreeNode* pChild = pCur->left ? pCur->left : pCur->right;

			if (pParent == NULL)
			{
				// 删除的是根节点
				tree->root = pChild;
				free(pCur);
				return;
			}

			if (pParent->left == pCur)
			{
				pParent->left = pChild;
			}
			else
			{
				pParent->right = pChild;
			}

			free(pCur);
			return;
		}
	}
}

/********************* 深度优先遍历 *********************/

// 先序遍历
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

// 中序遍历
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

// 后序遍历
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

/********************* 广度优先遍历 *********************/

void bst_levelorder(BST* tree)
{
	if (tree == NULL || tree->root == NULL)
	{
		printf("BST search failed, BST is empty or not initialized\n");
		return;
	}

	Queue* q = queue_create();
	queue_push(q, tree->root);
	
	while (!queue_empty(q))
	{
		TreeNode* pCur = queue_pop(q);
		printf("%3d ", pCur->key);

		if (pCur->left)
		{
			queue_push(q, pCur->left);
		}

		if (pCur->right)
		{
			queue_push(q, pCur->right);
		}
	}
	printf("\n");
}

void bst_levelorder2(BST* tree)
{
	if (tree == NULL || tree->root == NULL)
	{
		printf("BST search failed, BST is empty or not initialized\n");
		return;
	}

	Queue* q = queue_create();
	queue_push(q, tree->root);
	
	K first_node_key = 0;
	bool is_next_level_first_node = true;

	while (!queue_empty(q))
	{
		TreeNode* pCur = queue_pop(q);

		// && !is_next_level_first_node 的作用
		// 为了避免 root->key 与始初始化 first_node_key 时出现值相等导致多打印 \n 的问题
		if (first_node_key == pCur->key && !is_next_level_first_node)
		{
			printf("\n");
			is_next_level_first_node = true;
		}

		printf("%3d ", pCur->key);

		if (pCur->left)
		{
			queue_push(q, pCur->left);

			if (is_next_level_first_node)
			{
				first_node_key = pCur->left->key;
				is_next_level_first_node = false;
			}
		}

		if (pCur->right)
		{
			queue_push(q, pCur->right);

			if (is_next_level_first_node)
			{
				first_node_key = pCur->right->key;
				is_next_level_first_node = false;
			}
		}
	}
	printf("\n");
}