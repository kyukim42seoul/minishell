# include "proto.h"

int	parse_tree(t_info *info)
{
	t_token	*token;
	t_tree	*tree;

	token = info->t_head->next;
	tree = 0;
	tree = tree_pipe(tree, token);				//기본 트리 생성
	while (token->next)
	{
		printf("treeing : %d : %s\n", token->type, token->data);
		if (token->type == PIPE)
			tree = tree_pipe(tree, token);
		else if (token->type >= LEFT_REDI && token->type <= RIGHT_DOUBLE_REDI)
			tree = tree_io(tree, token);
		else if (token->type == CMD || token->type == BUILTIN)
			tree = tree_bin(tree, token);
		token = token->next;
	}
	if (token->type == PIPE)
			tree = tree_pipe(tree, token);
	print_tree(tree, 0);
	return (EXIT_SUCCESS);
}
