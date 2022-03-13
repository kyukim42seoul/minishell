#include "proto.h"

int	init_info(t_info **info)
{
	(*info) = malloc(sizeof(t_info));
	(*info)->cmd = 0;
	(*info)->pipe_flag = 0;
	(*info)->redirection_flag = -1;
	(*info)->double_shift_flag = -1;
	(*info)->debug = (t_debug *)malloc(sizeof(t_debug));
	(*info)->root = 0;
	return (EXIT_SUCCESS);
}
