#include "../proto.h"

int	tree_hub(t_tree *root, t_tree *new_node, int child_number)
{
	if (new_node->type == PIPE)
	{
		root = tree_pipe(root, new_node);
		child_number++;
	}
	else if (new_node->type >= LEFT_REDI \
		&& new_node->type <= RIGHT_DOUBLE_REDI)
		root = tree_io(root, new_node);
	else if (new_node->type == CMD || new_node->type == BUILTIN)
		root = tree_bin(root, new_node);
	else if (new_node->type == CHARACTERS)
		root = tree_arg(root, new_node);
	return (child_number);
}

int	parse_tree(t_info *info)
{
	t_token		*token;
	t_tree		*root;
	t_tree		*new_node;
	int			child_number;

	if (info->t_head == NULL)
		return (EXIT_FAILURE);
	if (info->t_head->next == NULL)
		return (EXIT_FAILURE);
	child_number = 0;
	token = info->t_head->next;
	root = 0;
	new_node = 0;
	root = tree_pipe(root, NULL);
	while (token)
	{
		new_node = dup_node(token, child_number);
		child_number = tree_hub(root, new_node, child_number);
		token = token->next;
	}
	info->root = root;
	return (EXIT_SUCCESS);
}
