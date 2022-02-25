#include "proto.h"

char **made(t_info *info)
{
	char **s = NULL;
	int len;
	t_token *check;

	len = 1;
	check = info->t_head->next;
	while (check->next != NULL)
	{
		check = check->next;
		len++;
	}
	char **str  = malloc(sizeof(char *) * (len + 1));
	s = str;
	check = info->t_head->next;
	while (check->next != NULL)
	{
		*str = ft_strdup(check->data);
		check = check->next;
		str++;
	}
	*str = ft_strdup(check->data);
	str++;
	*str = NULL;
	
	return (s);
}

/*
	[예시]
	export test 		-> export 에서 출력 o, env 에서 출력 x
	export test= 		-> export 에서 출력 o, env 에서 출력 o 대신 value = "" 인 상태
	export test1 test2	-> export 에서 출력 o test1, test2 총 두개가 올라감, env 에서 출력 x
	export test1= test2	-> export 에서 출력 o test1, test2 총 두개가 올라감, env 에서 test1 만 출력. 대신 value = "" 인 상태
*/
void	builtin_export(t_info *info, int fd)
{
	char **str;

	str = made(info);
	printf("%d\n", fd);
}

void	builtin_env(t_info *info, int fd)
{
	t_list *check;

	check = info->head;
	while (check->next != NULL)
	{
		if (check->content != NULL)
		{	
			ft_putstr_fd((char *)check->key, fd);
			ft_putchar_fd('=', fd);
			ft_putstr_fd((char *)check->content, fd);
			ft_putchar_fd('\n', fd);
		}
		check = check->next;
	}
	if (check->content != NULL)
	{	
		ft_putstr_fd((char *)check->key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd((char *)check->content, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	implement_cmd(t_info *info, int *exit_signal)
{
	int fd[2];

	*exit_signal = 0;
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO; 
	if (!ft_strncmp("env", info->t_head->next->data, 4))
		builtin_env(info, fd[1]);
	else if (!ft_strncmp("export", info->t_head->next->data, 7))
		builtin_export(info, fd[1]);
	// else if (ft_strncmp("unset", cmd, 6))
	// 	builtin_unset(info, exit_signal);
	// else if (ft_strncmp("pwd", cmd, 4))
	// 	builtin_pwd(info, exit_signal);
	// else if (ft_strncmp("cd", cmd, 3))
	// 	builtin_cd(info, exit_signal);
	// else if (ft_strncmp("echo", cmd, 5))
	// 	builtin_echo(info, exit_signal);
	// else if (ft_strncmp("exit", cmd, 5))
	// 	builtin_exit(info, exit_signal);
	
}