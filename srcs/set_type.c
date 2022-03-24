#include "proto.h"

void	set_type_cmd(t_token *cur, int *cmd_flag, int *redir_flag)
{
	if (cur->prev->type == PIPE && cur->type == CHARACTERS)
	{
		cur->type = CMD;
		*cmd_flag = 0;
	}
	if (cur->type >= LEFT_REDI && cur->type <= RIGHT_DOUBLE_REDI)
	{
		*cmd_flag = 0;
		*redir_flag = 1;
	}
	else if (*redir_flag == 1 && cur->type == CHARACTERS)
	{
		*redir_flag = 0;
		*cmd_flag = 1;
	}
	else if (*cmd_flag == 1 && cur->type == CHARACTERS)
	{
		cur->type = CMD;
		*cmd_flag = 0;
	}
	if (cur->type == PIPE)
		*cmd_flag = 1;
	if (cur->type == BUILTIN)
		*cmd_flag = 0;
}

int	set_type(t_token *head)
{
	int		cmd_flag;
	int		redir_flag;
	t_token	*cur;

	cmd_flag = 1;
	redir_flag = 0;
	cur = 0;
	if (head == NULL)
		return (EXIT_FAILURE);
	cur = head->next;
	while (cur->next)
	{
		set_type_cmd(cur, &cmd_flag, &redir_flag);
		cur = cur->next;
	}
	if (cur->prev->type == PIPE && cur->type == CHARACTERS)
		cur->type = CMD;
	else if (cmd_flag == 1 && cur->type == CHARACTERS)
	{
		cur->type = CMD;
		cmd_flag = 0;
	}
	return (EXIT_SUCCESS);
}
