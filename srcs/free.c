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
	info->my_num = 0;
}
