#include "proto.h"

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

t_token	*find_heredoc(t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur->next)
	{
		if (cur->type == LEFT_DOUBLE_REDI)
			return (cur);
		cur = cur->next;
	}
	return (token);
}
