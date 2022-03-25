#include "../../include/minishell.h"

t_tree	*dup_node(t_token *token, int child_number, int child_child)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->type = token->type;
	new->data = (char **)malloc(sizeof(char *) * 2);
	new->data[0] = ft_strdup(token->data);
	new->data[1] = NULL;
	new->left = NULL;
	new->right = NULL;
	new->prepip = -1;
	new->my_number = child_number;
	new->my_my = child_child;
	return (new);
}

t_tree	*type_only_node(int type)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->data = (char **)malloc(sizeof(char *) * 2);
	new->data[0] = NULL;
	new->data[1] = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	left_subtree(t_tree *root, t_tree *sub)
{
	if (root->left != NULL)
		postorder_del_tree(root->left);
	root->left = sub;
}

void	right_subtree(t_tree *root, t_tree *sub)
{
	if (root->right != NULL)
		postorder_del_tree(root->right);
	root->right = sub;
}

t_tree	*tree_search_type(t_tree *root, int type)
{
	t_tree	*buf;

	buf = 0;
	if (root == NULL)
		return (NULL);
	if (root->type == type)
	{
		buf = root;
		return (buf);
	}
	buf = tree_search_type(root->left, type);
	if (buf)
		return (buf);
	buf = tree_search_type(root->right, type);
	if (buf)
		return (buf);
	return (buf);
}
