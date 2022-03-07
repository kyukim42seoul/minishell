# include "../proto.h"

void	del_node(t_tree *node)
{
	static int	call_number;
	int			index;

	index = 0;
	call_number++;
	if (node == NULL)
		return ;
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

t_tree	*dup_node(t_token *token)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->type = token->type;
	new->data = (char **)malloc(sizeof(char *) * 2);
	new->data[0] = token->data;
	new->data[1] = NULL;
	new->left = NULL;
	new->right = NULL;
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

t_tree	*tree_pipe(t_tree *root, t_tree *new)
{
	t_tree	*buf;
	t_tree	*cur_root;

	buf = 0;
	cur_root = root;
	if (root == 0)
	{
		buf = type_only_node(PSPIPE);
		buf->data[0] = ft_strdup("|");
		buf->left = type_only_node(PSCMD);
		buf->left->left = type_only_node(PSIO);
		buf->left->left->left = type_only_node(PSREDIR);
		buf->left->right = type_only_node(PSBIN);
		root = buf;
	}
	else
	{
		while (cur_root->right != NULL)
			cur_root = cur_root->right;
		buf = new;
		buf->left = type_only_node(PSCMD);
		buf->left->left = type_only_node(PSIO);
		buf->left->left->left = type_only_node(PSREDIR);
		buf->left->right = type_only_node(PSBIN);
		cur_root->right = buf;
	}
	return (root);
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

int	check_io_leaf(t_tree *io_node)
{
	if (io_node->left->left)
		return (1);
	else
		return (0);
}

t_tree	*tree_io(t_tree *root, t_tree *new)
{
	t_tree	*buf;
	t_tree	*cmd_node;
	t_tree	*io_node;
	t_tree	*cur_root;

	buf = 0;
	cmd_node = 0;
	io_node = 0;
	cur_root = root;
	while (cur_root->right != NULL)
		cur_root = cur_root->right;
	cmd_node = tree_search_type(cur_root, PSCMD);
	if (new->type == LEFT_DOUBLE_REDI)
	{
		if (cmd_node->left->left->left)
		{
			buf = cmd_node->left;
			cmd_node->left = type_only_node(PSIO);
			cmd_node->left->right = buf;
			left_subtree(cmd_node->left, type_only_node(PSREDIR));
			left_subtree(cmd_node->left->left, new);
		}
		else
			left_subtree(cmd_node->left->left, new);
	}
	else
	{
		io_node = cmd_node->left;
		if (!check_io_leaf(io_node))
			left_subtree(io_node->left, new);
		else
		{
			while (io_node->right)
				io_node = io_node->right;
			right_subtree(io_node, type_only_node(PSIO));
			left_subtree(io_node->right, type_only_node(PSREDIR));
			left_subtree(io_node->right->left, new);
		}
	}
	return (root);
}

t_tree	*tree_bin(t_tree *root, t_tree *new)
{
	t_tree	*cur_root;
	t_tree	*bin_node;

	bin_node = 0;
	cur_root = root;
	while (cur_root->right != NULL)
		cur_root = cur_root->right;
	bin_node = tree_search_type(cur_root, PSBIN);
	left_subtree(bin_node, new);
	return (root);
}

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