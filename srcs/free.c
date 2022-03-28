/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:09:21 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/28 18:41:39 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	del_token(t_token *head)
{
	t_token	*temp;

	if (head != NULL)
	{
		while (head)
		{
			temp = head->next;
			if (head->data)
				free(head->data);
			free(head);
			head = NULL;
			head = temp;
		}
	}
	temp = NULL;
}

void	free_before_newline(t_info *info)
{
	del_token(info->t_head);
	postorder_del_tree(info->root);
	free(info->heredoc);
}
