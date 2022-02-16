# include "proto.h"

int	check_status_type(char c)
{
	if (ft_isalnum(c))
		return (CHARACTERS);
	else if (c == ' ')
		return (FTSPACE);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (LEFT_REDI);
	else if (c == '>')
		return (RIGHT_REDI);
	else if (c == '$')
		return (PATH);
	else if (c == '\'')
		return (SINGLE);
	else if (c == '\"')
		return (DOUBLE);
	return (CHARACTERS);
}

int path_len(char *cmd, int i)
{
	int len;
	int type;

	len = 0;
	while (cmd[i])
	{
		type = check_status_type(cmd[i]);
		if (type != CHARACTERS)
			break ;
		i++;
		len++;
	}
	return (len);
}

char	*path_change_check(char *cmd, t_info *info)
{
	int i;
	int type;
	int quotat;
	t_flag flag;

	quotat = 0;
	i = 0;
	flag.num = 0;
	while (cmd[i])
	{
		type = check_status_type(cmd[i]);
		if (type == DOUBLE)
		{
			if (quotat == 0)
				quotat = DOUBLE;
			else if (quotat == DOUBLE)
				quotat = 0;
		}
		else if (type == SINGLE)
		{
			if (quotat == 0)
				quotat = SINGLE;
			else if (quotat == SINGLE)
				quotat = 0;
		}
		else if ((type == PATH) && (quotat != SINGLE))
		{
			flag.len[flag.num] = path_len(cmd, i + 1);
			flag.i_cur[flag.num] = i;
			flag.num++;
		}
		i++;	
	}
	return (chang_cmd_to_env(cmd, flag, info));
}

int quotation_check(char *s, int i)
{
	int status;

	status = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			if (status == 0)
				status = 1;
			else if (status == 1)
				status = 0;
		}
		else if (s[i] == '\"')
		{
			if (status == 0)
				status = 2;
			else if (status == 2)
				status = 0;
		}
		i++;
		while (s[i] && (s[i] !=  '\"' &&  s[i] != '\''))
		 	i++;
	}
	return (status);
}

void	input_tokenize(char *full_command, t_info *info)
{
	//int		index;
	//char *cmd;

	if (!full_command)
		return ;
	info->t_head = NULL;
	if (quotation_check(full_command, 0))
		return (exit(-1));
	full_command = path_change_check(full_command, info);

	// splited = command_split(full_command);

	// while (**splited)
	// {
	// 	current->data = **splited;
	// 	current->type = check_type(**splited);
	// 	sh_lstadd_back(&info->t_head, current);
	// 	splited++;
	// }
	// check = info->t_head->next;
}