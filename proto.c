#include "proto.h"

void	interrupt(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(int argc, char *argv[], char *env[])
{
	// int		temp_argc;
	// char	**temp_argv;
	// char	**temp_env;
	char	*full_cmd;

	// temp_argc = argc;
	// temp_argv = argv;
	// temp_env = env;
	signal(SIGINT, interrupt);
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
