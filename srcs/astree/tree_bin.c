/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:08:14 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/25 19:08:15 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
