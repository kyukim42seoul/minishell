#include "../proto.h"

int	echo_option_check(char *str)
{
	int i;

	i = 2;
	if (str == NULL)
		return (0);
	if (ft_strncmp("-n", str, 2) != 0)
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_echo(t_info *info, int fd, int *exit_signal)
{
	int option;
	char	**str;
	int i;

	str = made_temp(info);
	option = 0;
	i = 1;
	if (str[i] ==  NULL)
		ft_putchar_fd('\n', fd);
	else
	{
		while (echo_option_check(str[i++]))
			option = 1;
		i--;
		while (str[i])
		{
			ft_putstr_fd(str[i], fd);
			if (str[i + 1])
				ft_putchar_fd(' ', fd);
			i++;
		}
		if (option == 0)
			ft_putchar_fd('\n', fd);
	}
	*exit_signal = 0;
}
