#include "tree.h"

void	connect_left(t_tree *node, t_ree *sub)
{
	if (node->left != NULL)
		node->left = NULL;
	node->left = sub;
}

void	connect_right(t_tree *node, t_ree *sub)
{
	if (node->right != NULL)
		node->right = NULL;
	node->right = sub;
}

void	get_left(t_tree *node)
{
	return (node->left->value);
}

void	get_right(t_tree *node)
{
	return (node->right->value);
}

