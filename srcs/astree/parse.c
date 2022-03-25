/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:08:07 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/25 19:41:11 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tree_hub(t_tree *root, t_tree *new_node, int *child_number, \
		int *child_child)
{
	if (new_node->type == PIPE)
	{
		root = tree_pipe(root, new_node);
		(*child_number)++;
		(*child_child) = 0;
	}
	else if (new_node->type >= LEFT_REDI \
		&& new_node->type <= RIGHT_DOUBLE_REDI)
	{
		root = tree_io(root, new_node);
		if (new_node->type == LEFT_DOUBLE_REDI)
			(*child_child)++;
	}
	else if (new_node->type == CMD || new_node->type == BUILTIN)
		root = tree_bin(root, new_node);
	else if (new_node->type == CHARACTERS)
		root = tree_arg(root, new_node);
}

int	parse_tree(t_info *info)
{
	t_token		*token;
	t_tree		*root;
	t_tree		*new_node;
	int			child_number;
	int			child_child;

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
	while (token)
	{
		new_node = dup_node(token, child_number, child_child);
		tree_hub(root, new_node, &child_number, &child_child);
		token = token->next;
	}
	print_tree(root, 0);
	info->root = root;
	return (EXIT_SUCCESS);
}
