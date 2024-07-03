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
			// ���� key ֵ��λ�� new_key > cur_key,���������ߣ���Ȼ����������
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
				// key�������ߣ�keyС������
				pCur = key > pCur->key ? pCur->right : pCur->left;
			}

			// pNewС���뵽���ӣ�pNew����뵽�Һ���
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

		// �ҵ�Ҫɾ���Ľڵ�
		while (pCur)
		{
			if (pCur->key == key)break;
			pParent = pCur;
			pCur = key > pCur->key ? pCur->right : pCur->left;
		}

		// û�ҵ��ýڵ�
		if (pCur == NULL)
		{
			printf("BST delete node failed, no such node\n");
			return;
		}

		// case a : ��ɾ���ڵ����������ӣ��������������ֱ��ǰ�����̴�������ת��Ϊcase b or c
		if (pCur->left && pCur->right)
		{
			/*

			// ������ֱ��ǰ���ڵ� �������
			TreeNode* pPre = pCur->left;
			TreeNode* pPre_parent = pCur;

			// ���������������½ڵ�
			while (pPre->right)
			{
				pPre_parent = pPre;
				pPre = pPre->right;
			}
			// ת��Ϊ case b or c
			pCur->key = pPre->key;
			pCur = pPre;
			pParent = pPre_parent;

			*/

			// ������ֱ�Ӻ�̽ڵ� �ҵ�����
			TreeNode* pPost = pCur->right;
			TreeNode* pPost_parent = pCur;

			// ���������������½ڵ�
			while (pPost->left)
			{
				pPost_parent = pPost;
				pPost = pPost->left;
			}

			// ת��Ϊcase b or c
			pCur->key = pPost->key;
			pCur = pPost;
			pParent = pPost_parent;
		}

		// case a : ��ɾ���ڵ�û�к��ӣ�ֱ��ɾ�������ڵ�ָ���ΪNULL
		if (pCur->left == NULL && pCur->right == NULL)
		{
			if (pParent == NULL)
			{
				// ɾ�����Ǹ��ڵ�
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

		// case c : ��ɾ���ڵ���һ�����ӣ��ø��ڵ�ָ��ָ���亢��
		if (pCur->left || pCur->right)
		{
			TreeNode* pChild = pCur->left ? pCur->left : pCur->right;

			if (pParent == NULL)
			{
				// ɾ�����Ǹ��ڵ�
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

/********************* ������ȱ��� *********************/

// �������
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

// �������
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

// �������
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

/********************* ������ȱ��� *********************/

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

		// && !is_next_level_first_node ������
		// Ϊ�˱��� root->key ��ʼ��ʼ�� first_node_key ʱ����ֵ��ȵ��¶��ӡ \n ������
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