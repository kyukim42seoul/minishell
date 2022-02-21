# include "proto.h"

int quotation_len(char *s, int i, int type)
{
	int len;

	len = 0;
	if (type == SINGLE)
	{
		i++;
		while (s[i])
		{
			if (s[i] == '\'')
				break ;
			len++;
			i++;
		}
	}
	else if (type == DOUBLE)
	{
		i++;
		while (s[i])
		{
			if (s[i] == '\"')
				break ;
			len++;
			i++;
		}
	}
	len = len + 2;
	return(len);
}

int	token_len_check(char *s, int i, t_flag *flag)
{
	if (flag->type[flag->num] == CHARACTERS)
		return (characters_len(s, i));
	else if (flag->type[flag->num] == SINGLE || flag->type[flag->num] == DOUBLE)
		return (quotation_len(s, i, flag->type[flag->num]));
	else if (flag->type[flag->num] == RIGHT_REDI)
	{
		if (s[i + 1] && s[i + 1] == '>')
		{
			flag->type[flag->num] = RIGHT_DOUBLE_REDI;
			return (2);
		}
	}
	else if (flag->type[flag->num] == LEFT_REDI)
	{
		if (s[i + 1] && s[i + 1] == '<')
		{
			flag->type[flag->num] = LEFT_DOUBLE_REDI;
			return (2);
		}
	}
	return (1);
}

void	token_insert(t_info *info, int type, char *data)
{
	t_token	*current;

	current = kb_lstnew();
	current->type = type;
	current->data = data;
	if (info->t_head == NULL)
	{
		info->t_head = current;
		info->t_head->prev = NULL;
	}
	if (info->t_head != current)
		current->prev = kb_lstlast(info->t_head);
	kb_lstlast(info->t_head)->next = current;
	current->next = NULL;
}

void	make_token_node(char *cmd, t_flag flag, t_info *info)
{
	int i;

	info->t_head = NULL;
	i = 0;
	while (i < flag.num)
	{
		if (flag.type[i] == SINGLE || flag.type[i] == DOUBLE)
			token_insert(info, CHARACTERS,
				ft_substr(cmd, flag.i_cur[i] + 1, flag.len[i] - 2));
		else
			token_insert(info, flag.type[i],
				ft_substr(cmd, flag.i_cur[i], flag.len[i]));
		i++;
	}
	print_t_token(info);
}

