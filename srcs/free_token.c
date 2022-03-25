#include "../include/minishell.h"

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
