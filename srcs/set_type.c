# include "proto.h"

int	set_type(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	if (cur == NULL)
		return (EXIT_FAILURE);
	while (cur->next)
	{
		if (cur->prev->type == PIPE && cur->type == CHARACTERS)
			cur->type = CMD;
		cur = cur->next;
	}
	if (cur->prev->type == PIPE && cur->type == CHARACTERS)
		cur->type = CMD;
	return (EXIT_SUCCESS);
}
