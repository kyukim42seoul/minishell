#include "../proto.h"

void	builtin_env(t_info *info, char **str)
{
	t_list *check;

	if (*(++str))
	{
		if (((*str)[0] == '-' && (*str)[1] && (*str)[1] != '-')
			|| ((*str)[0] == '-' && (*str)[1] && (*str)[1] == '-' && (*str)[2]))
		{
			printf("env: illegal option -- %c\n", (*str)[1]);
			printf("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
			printf("            [name=value ...] [utility [argument ...]]\n");
			exit_signal = 1;
		}
		else
		{
			printf("env: %s: No such file or directory\n", *str);
			exit_signal = 127;
		}
		return ;
	}
	check = info->e_head;
	while (check != NULL)
	{
		if (check->content != NULL)
		{	
			ft_putstr_fd((char *)check->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd((char *)check->content, 1);
			ft_putchar_fd('\n', 1);
		}
		check = check->next;
	}
}