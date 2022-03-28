/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:09:21 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/28 18:33:14 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_token(t_token *head)
{
	t_token	*cur;
	t_token	*buf;

	cur = head->next;
	while (cur->next)
	{
		buf = cur->next;
		if (cur->data)
			free(cur->data);
		free(cur);
		cur = buf;
	}
	if (cur->data)
		free(cur->data);
	free(cur);
	if (head->data)
		free(head->data);
	free(head);
}

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
	//del_heredoc(info->heredoc);
	postorder_del_tree(info->root);
	free(info->heredoc);
}
