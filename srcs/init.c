#include "../include/minishell.h"

int	init_info(t_info **info)
{
	(*info) = malloc(sizeof(t_info));
	(*info)->debug = (t_debug *)malloc(sizeof(t_debug));
	(*info)->my_num = 0;
	(*info)->root = 0;
	return (EXIT_SUCCESS);
}
