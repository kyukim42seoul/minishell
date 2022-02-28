#include "proto.h"

char **made_temp(t_info *info)
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

void	print_export(t_info *info, int fd)
{
	t_list *check;

	check = info->head;
	while (check != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd((char *)check->key, fd);
		ft_putchar_fd('=', fd);
		ft_putchar_fd('"', fd);
		ft_putstr_fd((char *)check->content, fd);
		ft_putstr_fd("\"\n", fd);
		check = check->next;
	}
}

int	str_len(char **str)
{
	int len;
	char **temp;

	len = 0;
	temp = str;
	while (*temp)
	{
		len++;
		temp++;
	}
	return (len);
}

int before_value(char *str)
{
	int i;

	i = 0;
	while (*str && *str != '=')
	{
		if (!ft_isalpha(*str) && *str != '_')
			return (0);
		i++;
		str++;
	}
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_' && *str != '=')
			retrun (0);
		str++;
	}
	return (i);
}

/*
	[예시]
	export test 		-> export 에서 출력 o, env 에서 출력 x
	export test= 		-> export 에서 출력 o, env 에서 출력 o 대신 value = "" 인 상태
	export test1 test2	-> export 에서 출력 o test1, test2 총 두개가 올라감, env 에서 출력 x
	export test1= test2	-> export 에서 출력 o test1, test2 총 두개가 올라감, env 에서 test1 만 출력. 대신 value = "" 인 상태
*/
void	builtin_export(t_info *info, int fd, int *exit_signal)
{
	char	**str;
	int		len;
	int 	i;

	str = made_temp(info);
	len = str_len(str);
	if (len == 1)
		print_export(info, fd);
	else
	{
		while (*(++str))
		{
			i = before_value(*str);
			if (i == 0)
			{
				printf("bash: export: `%s': not a valid identifier\n", *str);
				*exit_signal= 1;
			}
			else if (i == ft_strlen(*str) && *str[i] == '=')
				export_num_value(); //밸류가 빈문자열 ""  ex) export kk= 
			else
			{
				//export kk  				밸류가  null 이거나
				//export kk=aa  		밸류가 있을 때.
			}
		}
	}

	printf("%d\n", fd);
}

void	builtin_env(t_info *info, int fd)
{
	t_list *check;

	check = info->head;
	while (check != NULL)
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
		builtin_export(info, fd[1], exit_signal);
	else if (!ft_strncmp("unset", info->t_head->next->data, 6))
		builtin_unset(info, exit_signal);
	// else if (!ft_strncmp("pwd", cmd, 4))
	// 	builtin_pwd(info, exit_signal);
	// else if (!ft_strncmp("cd", cmd, 3))
	// 	builtin_cd(info, exit_signal);
	// else if (!ft_strncmp("echo", cmd, 5))
	// 	builtin_echo(info, exit_signal);
	// else if (!ft_strncmp("exit", cmd, 5))
	// 	builtin_exit(info, exit_signal);
	
}