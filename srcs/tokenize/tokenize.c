# include "../proto.h"

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

int characters_len(char *cmd, int i)
{
	int len;
	int type;

	len = 0;
	while (cmd[i])
	{
		type = check_status_type(cmd[i]);
		if (type != CHARACTERS)
			break ;
		len++;
		i++;
	}
	return (len);
}

char	*path_change_check(char *cmd, t_info *info)
{
	int i;
	int quotat;
	t_flag flag;

	i = 0;
	quotat = 0;
	flag.num = 0;
	while (cmd[i])
	{
		flag.type[0] = check_status_type(cmd[i]);
		if (flag.type[0]  == DOUBLE)
		{
			if (quotat == 0)
				quotat = DOUBLE;
			else if (quotat == DOUBLE)
				quotat = 0;
		}
		else if (flag.type[0]  == SINGLE)
		{
			if (quotat == 0)
				quotat = SINGLE;
			else if (quotat == SINGLE)
				quotat = 0;
		}
		else if ((flag.type[0]  == PATH) && (quotat != SINGLE))
		{
			flag.len[flag.num] = characters_len(cmd, i + 1);
			flag.i_cur[flag.num] = i;
			flag.num++;
		}
		i++;	
	}
	return (change_cmd_to_env(cmd, flag, info));
}

void	tokenize(char *full_command, t_info *info)
{
	int		i;
	int 	type;
	t_flag	flag;

	info->t_head = NULL;
	full_command = path_change_check(full_command, info);
	flag.num = 0;
	i = 0;
	while (full_command[i])
	{
		type = check_status_type(full_command[i]);
		if (type != FTSPACE)
		{
			flag.i_cur[flag.num] = i;
			flag.type[flag.num] = type;
			flag.len[flag.num] = token_len_check(full_command, i, &flag);
			i = i + flag.len[flag.num];
			flag.num++;
		}
		else
			i++;
	}
	make_token_node(full_command, flag, info);
}