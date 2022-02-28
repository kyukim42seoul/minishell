#include "proto.h"

int	valid_key(char *str)
{
	while (*str)
	{
		if (!ft_isalpha(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	rm_env(t_info *info, char *str)
{
	t_list *check;
	t_list *temp;

	check = info->head;
	while (check)
	{
		if (!ft_strncmp(str, check->key, ft_strlen(check->key)))
		{
			if (check == info->head)
				info->head = check->next;
			else
				temp->next = check->next;
			free(check->key);
			free(check->content);
			free(check);
		}
		temp = check;
		check =  check->next;
	}
}

void	builtin_unset(t_info *info, int *exit_signal)
{
	char	**str;
	int		len;

	str = made_temp(info);
	len = str_len(str);
	if (len > 1)
	{
		while (*(++str))
		{
			if (valid_key(*str))
				rm_env(info, *str);
			else
			{
				printf("bash: unset: `%s': not a valid identifier\n", *str);
				*exit_signal = 1;	
			}
		}
	}
}