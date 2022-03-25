/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:08:17 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/25 19:08:17 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	replace_order(t_tree *cmd_node, t_tree *new)
{
	t_tree	*buf;

	buf = cmd_node->left;
	cmd_node->left = type_only_node(PSIO);
	cmd_node->left->right = buf;
	left_subtree(cmd_node->left, type_only_node(PSREDIR));
	left_subtree(cmd_node->left->left, new);
}

void	insert_heredoc(t_tree *buf, t_tree *io_node, t_tree *new)
{
	buf->right = type_only_node(PSIO);
	buf->right->left = type_only_node(PSREDIR);
	buf->right->left->left = new;
	buf->right->right = io_node;
}

void	tree_heredoc(t_tree *io_node, t_tree *cmd_node, t_tree *new)
{
	t_tree	*buf;
	t_tree	*leaf;

	buf = 0;
	leaf = 0;
	if (io_node->left->left)
	{
		leaf = io_node->left->left;
		if ((leaf->type >= LEFT_REDI && leaf->type <= RIGHT_REDI) \
				|| leaf->type == RIGHT_DOUBLE_REDI)
			replace_order(cmd_node, new);
		else
		{
			while (io_node \
				&& (io_node->left->left->type == LEFT_DOUBLE_REDI))
			{
				buf = io_node;
				io_node = io_node->right;
			}
			insert_heredoc(buf, io_node, new);
		}
	}
	else
		left_subtree(cmd_node->left->left, new);
}

void	add_io_tree(t_tree *io_node, t_tree *new)
{
	while (io_node->right)
		io_node = io_node->right;
	right_subtree(io_node, type_only_node(PSIO));
	left_subtree(io_node->right, type_only_node(PSREDIR));
	left_subtree(io_node->right->left, new);
}

t_tree	*tree_io(t_tree *root, t_tree *new)
{
	t_tree	*cmd_node;
	t_tree	*io_node;
	t_tree	*cur_root;

	cmd_node = 0;
	io_node = 0;
	cur_root = root;
	while (cur_root->right != NULL)
		cur_root = cur_root->right;
	cmd_node = tree_search_type(cur_root, PSCMD);
	io_node = cmd_node->left;
	if (new->type == LEFT_DOUBLE_REDI)
		tree_heredoc(io_node, cmd_node, new);
	else
	{
		io_node = cmd_node->left;
		if (!io_node->left->left)
			left_subtree(io_node->left, new);
		else
			add_io_tree(io_node, new);
	}
	return (root);
}
