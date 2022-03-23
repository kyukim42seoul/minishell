/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:46 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/23 20:32:40 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../proto.h"

void	preorder_traverse(t_info *info, t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type == PSIO)
	{
		if (tree->left && tree->left->left)
			redir_hub(tree);
	}
	else if (tree->type == CMD)
		implement_cmd(info, tree->data);
	preorder_traverse(info, tree->left);
	preorder_traverse(info, tree->right);
}

void	single_tree(t_info *info, t_tree *tree, int in, int out)
{
	preorder_traverse(info, tree);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}
