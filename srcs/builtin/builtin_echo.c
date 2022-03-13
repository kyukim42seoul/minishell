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

void	builtin_echo(char **str, int *exit_signal)
{
	int option;
	int i;

	option = 0;
	i = 1;
	if (str[i] ==  NULL)
		ft_putchar_fd('\n', 1);
	else
	{
		while (echo_option_check(str[i++]))
			option = 1;
		i--;
		while (str[i])
		{
			ft_putstr_fd(str[i], 1);
			if (str[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
		if (option == 0)
			ft_putchar_fd('\n', 1);
	}
	*exit_signal = 0;
}
