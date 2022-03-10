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

void	set_signal(int *exit_signal)
{
	struct termios term;

	*exit_signal = 0;
	//tcsetattr의 옵션으로 들어가는 optional_actions에 TCSNOW는 환경 변수 0으로 등록되어 있는데, 속성을 바로 변경한다는 것을 의미한다.
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, signal_handler); //ctrl + c
	signal(SIGQUIT, SIG_IGN); //ctrl + /
}


/*
	main 함수 설명
*/
int exit_signal;

int	main(int argc, char *argv[], char *env[])
{
	int		temp_argc;
	char	**temp_argv;
	char	*full_cmd;
	t_info	*info;
	t_token	*temp;

	temp_argc = argc;
	temp_argv = argv;
	set_signal(&exit_signal);
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
		tokenize(full_cmd, info);
		if (info->t_head != NULL)
		{
			temp = kb_lstnew();
			temp->type = PIPE;
			lstadd_front(&info->t_head, temp);
			info->t_head = temp;
		}
		set_type(info->t_head);
		if (syntax_hub(info->t_head, info->debug) == EXIT_FAILURE && info->t_head != NULL)
			printf("syntax error\npoint : %s\ndata : %s\n", info->debug->syntax_error, info->debug->error_point_data);
		parse_tree(info);
		action_tree(info, &exit_signal);
		add_history(full_cmd);
		// cur_tree = info->root;
		// while (cur_tree->right)
		// {
		// 	exec_pipe(cur_tree);
		// 	cur_tree = cur_tree->right;
		// }
		// exec_pipe(cur_tree);
//		while (check <= 0)
//			check = wait(&status);
//		printf("It's parent\n");
//		print_tree(info->root, 0);
//		implement_cmd(info, &exit_signal);
		free(full_cmd);
		postorder_del_tree(info->root);
		info->root = 0;
	}
	return (EXIT_SUCCESS);
}
