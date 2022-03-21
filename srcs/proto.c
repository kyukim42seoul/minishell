#include "proto.h"

void	signal_handler(int signum)
{
	pid_t pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			exit_signal = 1;
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else
		{
			exit_signal = 130;
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else if (signum == SIGQUIT)
	{
		if (pid == 0)
		{
			exit_signal = 131;
			write(1, "Quit: 3\n", 9);
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
			write(1, "  \b\b", 4);
		}
	}
	return ;
}


void	set_signal()
{
	struct termios term;

	exit_signal = 0;
	//tcsetattr의 옵션으로 들어가는 optional_actions에 TCSNOW는 환경 변수 0으로 등록되어 있는데, 속성을 바로 변경한다는 것을 의미한다.
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, signal_handler); //ctrl + c
	signal(SIGQUIT, signal_handler); //ctrl + /
}

int check_cmd(char *cmd)
{
	int i;

	if (*cmd == '\0')
		return (1);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 32 || (cmd[i] >= 9 && cmd[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}

/*
	main 함수 설명
*/
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
		else if (!check_cmd(full_cmd))
		{
			tokenize(full_cmd, info);
			add_head(info, PIPE);
			set_type(info->t_head);
			if (syntax_hub(info->t_head, info->debug) == EXIT_FAILURE && info->t_head != NULL)
				printf("syntax error\npoint : %s\ndata : %s\n", info->debug->syntax_error, (char *)info->debug->error_point_data);
			parse_tree(info);
			action(info);
			add_history(full_cmd);
			postorder_del_tree(info->root);
		}
		free(full_cmd);
		info->root = 0;
	}
	return (EXIT_SUCCESS);
}
