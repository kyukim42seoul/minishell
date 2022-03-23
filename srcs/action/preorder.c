/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:46 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/23 18:37:43 by kyukim           ###   ########.fr       */
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

void	single_tree(t_info *info, t_tree *tree)
{
	preorder_traverse(info, tree);
	info->double_shift_flag = 0;
}
