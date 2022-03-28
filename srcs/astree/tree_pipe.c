/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:08:21 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/25 19:08:22 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	basic_tree(t_tree *root)
{
	root->left = type_only_node(PSCMD);
	root->left->left = type_only_node(PSIO);
	root->left->left->left = type_only_node(PSREDIR);
	root->left->right = type_only_node(PSBIN);
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
		basic_tree(buf);
		root = buf;
	}
	else
	{
		while (cur_root->right != NULL)
			cur_root = cur_root->right;
		buf = new;
		basic_tree(buf);
		cur_root->right = buf;
	}
	return (root);
}
