#include "proto.h"

/*
pipe(3) 단독 -> 2(PIPE)
cmd(1, 2) : pipe(3) -> 10(BUILTIN), 12(CMD)
path, word(5) : pipe(3) cmd(1, 2) -> 0(CHARACTERS)
redir(4) : pipe(3) cmd(1, 2) {path, word(5)} + 뒤에 path, word(5) -> 3(<:LEFT_REDI), 4(>:RIGHT_REDI), 5(<<:LEFT_DOUBLE_REDI), 6(>>:RIGHT_DOUBLE_REDI)
*/

int	syntax_cmd(t_token *tokens,t_debug *debug)	// 앞에 PIPE 가 있어야 한다.
{
	if (tokens->prev->type != PIPE)
	{
		debug->syntax_error = ft_strdup("syntax_cmd\n");
		debug->error_point_data = tokens->data;
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}

int	syntax_pipe(t_token *tokens,t_debug *debug)	// 뒤에 BUILTIN 혹은 CMD 가 있어야 한다.
{
	t_token	*cur;

	cur = tokens->next;
	if (tokens->type == PIPE && tokens->prev == NULL)
		return (EXIT_SUCCESS);
	if (cur->type == BUILTIN || cur->type == CMD)
		return (syntax_cmd(cur, debug));
	else
	{
		debug->syntax_error = ft_strdup("syntax_pipe\n");
		debug->error_point_data = tokens->data;
		return (EXIT_FAILURE);
	}
}

int	syntax_redir(t_token *tokens,t_debug *debug)	// 앞에 PIPE 혹은 BUILTIN 혹은 CMD 가 있어야 한다. 뒤에 cmd(못 오나??) 혹은 characters 가 있어야 한다.
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
	else if (cur->prev->type == PIPE)
		return (syntax_pipe(cur->prev, debug));
	else if (cur->prev->type == CHARACTERS)
		return (syntax_word(cur->prev, debug));
	return (EXIT_SUCCESS);
}

int	syntax_word(t_token *tokens,t_debug *debug)	// 앞에 REDIR(or DOUBLE REDIR) 혹은 BUILTIN 혹은 CMD 가 있어야 한다.
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

int	check_order(t_token *tokens,t_debug *debug)
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

int	syntax_hub(t_token *head,t_debug *debug)		//양방향 리스트 / 0(OK), 1(FailL), 2(Not Complete)
{
	t_token	*cur;

	cur = 0;
	if (head == NULL)
		return (EXIT_FAILURE);
	cur = head->next;
	while (cur->next)
	{
		if (check_order(cur, debug) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		cur = cur->next;
	}
	if (check_order(cur, debug) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
