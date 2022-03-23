/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:16:46 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/23 17:18:17 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../proto.h"

void	preorder_traverse(t_info *info, t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type == PSIO)
	{
		if (tree->left)
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
