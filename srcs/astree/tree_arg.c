#include "../../include/minishell.h"

t_tree	*tree_arg(t_tree *root, t_tree *new)
{
	t_tree	*cur_root;
	t_tree	*io_node;
	t_tree	*bin_node;

	cur_root = root;
	while (cur_root->right != NULL)
		cur_root = cur_root->right;
	io_node = tree_search_type(cur_root, PSIO);
	bin_node = tree_search_type(cur_root, PSBIN);
	while (io_node->right != NULL && io_node->left->right != NULL)
		io_node = io_node->right;
	if (io_node->left->left && io_node->left->right == NULL)
	{
		io_node->left->right = new;
		return (root);
	}
	else
	{
		if (bin_node->left == NULL)
			bin_node->left = new;
		else
			bin_node->left->data = add_str(bin_node->left->data, new->data);
	}
	free (new);
	return (root);
}
