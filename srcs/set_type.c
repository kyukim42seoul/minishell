# include "proto.h"

int	set_type(t_token *head)
{
	t_token	*cur;

	cur = 0;
	if (head == NULL)
		return (EXIT_FAILURE);
	cur = head->next;
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
