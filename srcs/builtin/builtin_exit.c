#include "../proto.h"

void	builtin_exit(t_info *info, int *exit_signal)
{
	char **str;

	str = made_temp(info);
	if (*(++str) == NULL)
	{
		printf("exit(%d)\n", *exit_signal);
		exit(*exit_signal);
	}

}