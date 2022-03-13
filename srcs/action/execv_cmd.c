# include "../proto.h"

void	execv_cmd(t_info *info, char **str)
{
	if (execve(str[0], str, info->env) < 0)
		exit(0);
}