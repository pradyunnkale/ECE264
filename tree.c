// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "tree.h"

// DO NOT MODIFY FROM HERE --->>>
Tree * newTree(void)
{
  Tree * t = malloc(sizeof(Tree));
  t -> root = NULL;
  return t;
}

void deleteTreeNode(TreeNode * tr)
{
  if (tr == NULL)
    {
      return;
    }
  deleteTreeNode (tr -> left);
  deleteTreeNode (tr -> right);
  free (tr);
}

void freeTree(Tree * tr)
{
  if (tr == NULL)
    {
      // nothing to delete
      return;
    }
  deleteTreeNode (tr -> root);
  free (tr);
}


// <<<--- UNTIL HERE

// ***
// *** You MUST modify the follow function
// ***
#ifdef TEST_BUILDTREE
TreeNode * buildNode(int * inArray, int * postArray, int size);
TreeNode * buildNode(int * inArray, int * postArray, int size)
{
	if (size <= 0)
	{
		return NULL;
	}

	TreeNode * node = malloc(sizeof(TreeNode));
	if (node == NULL)
	{
		return NULL;
	}	

	node->value = postArray[size - 1];

	int rootidx = 0;
	while (inArray[rootidx] != node->value)
	{
		rootidx++;
	}

	node->left = buildNode(inArray, postArray, rootidx);
	node->right = buildNode(inArray + rootidx + 1, postArray + rootidx, size - rootidx - 1);

	return node;
}

Tree * buildTree(int * inArray, int * postArray, int size)
{
	Tree * tree = malloc(sizeof(Tree));
	if (tree == NULL)
	{
		return NULL;
	}

	tree->root = buildNode(inArray, postArray, size);
	return tree;
}
#endif

#ifdef TEST_PRINTPATH
int printPathHelper(TreeNode * node, int val);
int printPathHelper(TreeNode * node, int val)
{
	if (node == NULL)
	{
		return 0;
	}
	
	// Does the current node have the value 
	if (node->value == val)
	{
		printf("%d ", val);
		return 1;
	}
	
	// Is the current node in the path
	if (printPathHelper(node->left, val) || printPathHelper(node->right, val))
	{
		printf("%d ", node->value);
		return 1;
	}

	return 0;
}

void printPath(Tree * tr, int val)
{
	if (tr == NULL || tr->root == NULL)
	{
		return;
	}
	printPathHelper(tr->root, val);
	printf("\n");
}
#endif
