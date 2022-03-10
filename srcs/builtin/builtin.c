#include "../proto.h"

void	env_add(t_info *info, char *key, char *content)
{
	t_list *check;

	check = sh_lstnew(NULL);
	check->type = O_ENV;
	check->content = content;
	check->key = key;
	sh_lstadd_back(&info->head, check);
}

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

void	implement_cmd(t_info *info, char **cmd, int *exit_signal)
{
	int fd[2];

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO; 
	if (!ft_strncmp("env", cmd[0], 4))
		builtin_env(info, cmd, fd[1], exit_signal);
	else if (!ft_strncmp("export", cmd[0], 7))
		builtin_export(info, cmd, fd[1], exit_signal);
	else if (!ft_strncmp("unset", cmd[0], 6))
		builtin_unset(info, cmd, exit_signal);
	else if (!ft_strncmp("pwd", cmd[0], 4))
		builtin_pwd(cmd, fd[1], exit_signal);
	else if (!ft_strncmp("cd", cmd[0], 3))
		builtin_cd(info, cmd, exit_signal);
	else if (!ft_strncmp("echo", cmd[0], 5))
		builtin_echo(cmd, fd[1], exit_signal);
	else if (!ft_strncmp("exit", cmd[0], 5))
		builtin_exit(cmd, exit_signal);
}