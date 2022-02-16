#include "proto.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
	return ;
}

void	set_signal()
{
	struct termios term;

	//tcsetattr의 옵션으로 들어가는 optional_actions에 TCSNOW는 환경 변수 0으로 등록되어 있는데, 속성을 바로 변경한다는 것을 의미한다.
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, signal_handler); //ctrl + c
	signal(SIGQUIT, SIG_IGN); //ctrl + /
}

int	main(int argc, char *argv[], char *env[])
{
	int		temp_argc;
	char	**temp_argv;
	char	*full_cmd;
	t_info	*info;

	temp_argc = argc;
	temp_argv = argv;
	set_signal();
	init_info(&info);
	copy_env(info, env);
	while (1)
	{
		full_cmd = readline("in> ");
		if (full_cmd == NULL)
		{
			printf("\033[1A"); // 커서를 위로 한 줄 올린다.
           	printf("\033[4C"); // 커서를 4만큼 오른쪽으로 민다.
            printf("exit\n");
			exit (-1);
		}
		// info->cmd = ft_strdup(&full_cmd);
		input_tokenize(full_cmd, info);
		add_history(full_cmd);
		free(full_cmd);
	}
	return (EXIT_SUCCESS);
}
