#include "../proto.h"

int	valid_key(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	rm_env(t_info *info, char *str)
{
	t_list *check;
	t_list *temp;

	temp = NULL;
	check = info->e_head;
	while (check)
	{
		if (!ft_strncmp(str, check->key, ft_strlen(check->key)))
		{
			if (check == info->e_head)
				info->e_head = check->next;
			else
				temp->next = check->next;
			free(check->key);
			free(check->content);
			free(check);
			break ;
		}
		else
		{
			temp = check;
			check =  check->next;
		}
	}
	exit_signal = 0;
}

void	builtin_unset(t_info *info, char **str)
{
	int		len;

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
				exit_signal = 1;
			}
		}
	}
}

