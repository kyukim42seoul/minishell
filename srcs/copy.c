#include "../include/minishell.h"

int	copy_env(t_info *info, char *env[])
{
	int		index;
	int		lenth;
	t_list	*current;

	index = 0;
	lenth = 0;
	info->e_head = sh_lstnew(NULL);
	while (env[index] != NULL)
	{
		lenth = sh_strchr(env[index], '=') - env[index];
		current = sh_lstnew(NULL);
		current->type = O_ENV;
		current->content = ft_strdup(sh_strchr(env[index], '=') + 1);
		current->key = sh_substr(env[index], 0, lenth);
		sh_lstadd_back(&info->e_head, current);
		index++;
	}
	info->env_array = env;
	return (EXIT_SUCCESS);
}
