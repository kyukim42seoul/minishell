#include "../proto.h"

int	syntax_cmd(t_token *tokens, t_debug *debug)
{
	t_token	*temp_token;
	t_debug	*temp_debug;

	temp_token = tokens;
	temp_debug = debug;
	return (EXIT_SUCCESS);
}

int	syntax_pipe(t_token *tokens, t_debug *debug)
{
	t_token	*cur;

	cur = tokens->next;
	if (cur == NULL)
		return (EXIT_FAILURE);
	if (cur->type == PIPE)
		return (EXIT_FAILURE);
	if (tokens->type == PIPE && tokens->prev == NULL)
		return (EXIT_SUCCESS);
	if (cur->type == BUILTIN || cur->type == CMD)
		return (syntax_cmd(cur, debug));
	if (cur->type >= LEFT_REDI && cur->type <= RIGHT_DOUBLE_REDI)
		return (syntax_redir(cur, debug));
	else
	{
		debug->syntax_error = ft_strdup("syntax_pipe\n");
		debug->error_point_data = tokens->data;
		return (EXIT_FAILURE);
	}
}

int	syntax_redir(t_token *tokens, t_debug *debug)
{
	t_token	*cur;

	cur = tokens;
	if (cur->next == NULL)
	{
		debug->syntax_error = ft_strdup("syntax_redir : no argument\n");
		debug->error_point_data = cur->data;
		return (EXIT_FAILURE);
	}
	if (cur->next->type != CHARACTERS)
	{
		debug->syntax_error = ft_strdup("syntax_redir : invalid argument\n");
		debug->error_point_data = cur->data;
		return (EXIT_FAILURE);
	}
	if (cur->prev->type == BUILTIN || cur->type == CMD)
		return (syntax_cmd(cur->prev, debug));
	else if (cur->prev->type == CHARACTERS)
		return (syntax_word(cur->prev, debug));
	return (EXIT_SUCCESS);
}

int	syntax_word(t_token *tokens, t_debug *debug)
{
	t_token	*cur;

	cur = tokens->prev;
	while (cur->prev)
	{
		if (cur->type >= LEFT_REDI && cur->type <= RIGHT_DOUBLE_REDI)
			return (syntax_redir(cur, debug));
		else if (cur->type == BUILTIN || cur->type == CMD)
			return (syntax_cmd(cur, debug));
		else
			cur = cur->prev;
	}
	debug->syntax_error = ft_strdup("syntax_word\n");
	debug->error_point_data = tokens->data;
	return (EXIT_FAILURE);
}

int	check_order(t_token *tokens, t_debug *debug)
{
	if (tokens->type == PIPE)
		return (syntax_pipe(tokens, debug));
	else if (tokens->type == BUILTIN || tokens->type == CMD)
		return (syntax_cmd(tokens, debug));
	else if (tokens->type >= LEFT_REDI && tokens->type <= RIGHT_DOUBLE_REDI)
		return (syntax_redir(tokens, debug));
	else if (tokens->type == CHARACTERS)
		return (syntax_word(tokens, debug));
	else
	{
		debug->syntax_error = ft_strdup("undefined type\n");
		debug->error_point_data = tokens->data;
		return (EXIT_FAILURE);
	}
}
