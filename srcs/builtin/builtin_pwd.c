#include "../proto.h"

void	builtin_pwd(t_info *info, int fd, int *exit_signal)
{
	char *s;
	char **str;

	str = made_temp(info);
	if (*(++str))
	{
		if (((*str)[0] == '-' && (*str)[1] && (*str)[1] != '-')
			|| ((*str)[0] == '-' && (*str)[1] && (*str)[1] == '-' && (*str)[2]))
		{
			printf("bash: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n", (*str)[1]);
			*exit_signal= 1;
			return ;
		}
	}
	s = getcwd(NULL, 0);
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	free(s);
}