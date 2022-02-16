#include "proto.h"

int	copy_env(t_info *info, char *env[])
{
	int		index;
	int		lenth;
	t_list	*current;
	t_list	*check;

	index = 0;
	lenth = 0;
	info->head = NULL;
	while (env[index] != NULL)
	{
		lenth = sh_strchr(env[index], '=') - env[index];
		current = sh_lstnew(NULL);
		current->type = O_ENV;
		current->content = sh_strchr(env[index], '=') + 1;
		current->key = sh_substr(env[index], 0, lenth);
		sh_lstadd_back(&info->head, current);
		index++;
	}
	check = info->head->next;
	while (check->next != NULL)
	{
		printf("%s=%s\n", (char *)check->key, (char *)check->content);
		check = check->next;
	}
	printf("%s=%s\n", (char *)check->key, (char *)check->content);
	return (EXIT_SUCCESS);
}
