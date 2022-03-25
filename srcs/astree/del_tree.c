#include "../../include/minishell.h"

void	del_node(t_tree *node)
{
	int			index;

	index = 0;
	if (node == NULL)
		return ;
	if (node->prepip)
		close(node->prepip);
	if (node->pip[0])
		close (node->pip[0]);
	if (node->pip[1])
		close (node->pip[1]);
	if (node->data)
	{
		while (node->data[index])
		{
			free(node->data[index]);
			node->data[index] = NULL;
			index++;
		}
		free(node->data);
		node->data = NULL;
	}
	free(node);
	node = NULL;
}

void	postorder_del_tree(t_tree *root)
{
	if (root == NULL)
		return ;
	postorder_del_tree(root->left);
	postorder_del_tree(root->right);
	del_node(root);
}
