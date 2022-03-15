#include "../proto.h"

void	builtin_exit(char **str, int *exit_signal)
{
	int i;

	if (*(++str) == NULL)
	{
		printf("exit\n");
		exit(*exit_signal);
	}
	i = 0;
	while ((*str)[i])
	{
		if (!ft_isdigit((*str)[i++]))
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", *str);
			exit(255);
		}
	}
	if ((*(++str)) != NULL && (*exit_signal = 1))
		printf("bash: exit: too many arguments\n");
	else
	{
		printf("exit\n");
		exit(ft_atoi(*(--str)));
	}
}