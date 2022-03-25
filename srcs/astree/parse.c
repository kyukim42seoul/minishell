# include "../proto.h"

int	parse_tree(t_info *info)
{
	static int	test_index;
	t_token	*token;
	t_tree	*root;
	t_tree	*new_node;
	int		child_number;
	int		child_child;

	if (info->t_head == NULL)
		return (EXIT_FAILURE);
	if (info->t_head->next == NULL)
		return (EXIT_FAILURE);
	child_number = 0;
	child_child = 0;
	token = info->t_head->next;
	root = 0;
	new_node = 0;
	root = tree_pipe(root, NULL);
	while (token->next)
	{
		test_index++;
		new_node = dup_node(token, child_number, child_child);
		if (new_node->type == PIPE)
		{
			root = tree_pipe(root, new_node);
			child_number++;
			child_child = 0;
		}
		else if (new_node->type >= LEFT_REDI && new_node->type <= RIGHT_DOUBLE_REDI)
		{
			root = tree_io(root, new_node);
			child_child++;
		}
		else if (new_node->type == CMD || new_node->type == BUILTIN)
			root = tree_bin(root, new_node);
		else if (new_node->type == CHARACTERS)
			root = tree_arg(root, new_node);
//		print_tree(root, 0);																//tree 생성 과정 확인용
		token = token->next;
	}
	new_node = dup_node(token, child_number, child_child);
	if (new_node->type == PIPE)
		root = tree_pipe(root, new_node);
	else if (new_node->type >= LEFT_REDI && new_node->type <= RIGHT_DOUBLE_REDI)
		root = tree_io(root, new_node);
	else if (new_node->type == CMD || new_node->type == BUILTIN)
		root = tree_bin(root, new_node);
	else if (new_node->type == CHARACTERS)
		root = tree_arg(root, new_node);																	//완성된 트리
	info->root = root;
	return (EXIT_SUCCESS);
}
