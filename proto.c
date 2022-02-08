#include "proto.h"

int	main(int argc, char *argv[], char *env[])
{
	int		temp_argc;
	char	**temp_argv;
	char	**temp_env;
	char	*full_cmd;

	temp_argc = argc;
	temp_argv = argv;
	temp_env = env;
	while (1)
	{
		full_cmd = readline("> ");
		if (full_cmd == NULL)
			break ;
		add_history(full_cmd);
		free(full_cmd);
	}
	return (EXIT_SUCCESS);
}
