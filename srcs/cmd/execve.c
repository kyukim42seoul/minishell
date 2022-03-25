#include "../../include/minishell.h"

int	check_path(const char *path)
{
	int			result;
	struct stat	*path_info;

	path_info = (struct stat *)malloc(sizeof(struct stat *));
	if (stat(path, path_info) == 0)
	{
		if (S_ISDIR(path_info->st_mode))
			result = 2;
		result = 1;
	}
	else
		result = 0;
	return (result);
}

t_list	*make_relative_path(char *env_path, char *cmd)
{
	int		index;
	char	**divided_env;
	char	*buf;
	t_list	*head;
	t_list	*cur;

	index = 0;
	divided_env = ft_split(env_path, ':');
	head = sh_lstnew(NULL);
	while (divided_env[index])
	{
		buf = ft_strjoin(divided_env[index], "/");
		cur = sh_lstnew(ft_strjoin(buf, cmd));
		free(buf);
		sh_lstadd_back(&head, cur);
		index++;
	}
	return (head);
}

t_list	*find_valid_path(t_list	*path_head)
{
	int		result;
	t_list	*cur;

	result = -1;
	cur = path_head->next;
	while (cur->next)
	{
		result = check_path((char *)cur->content);
		if (result)
			return (cur);
		cur = cur->next;
	}
	result = check_path((char *)cur->content);
	if (result)
		return (cur);
	else
		return (NULL);
}

void	exit_signal_by_result(int result, char **cmd_data)
{
	if (result == 2)
	{
		printf("bash: %s: is a directory\n", cmd_data[0]);
		g_exit_signal = 126;
	}
	else if (result == 0)
	{
		printf("bash: %s: No such file or directory\n", cmd_data[0]);
		g_exit_signal = 127;
	}
}

void	run_execve(char **cmd_data, char *env_path, char **env_array)
{
	t_list	*head_relative_path_list;
	t_list	*valid_path;
	int		result;

	head_relative_path_list = 0;
	if (cmd_data[0][0] == '/')
	{
		result = check_path(cmd_data[0]);
		if (result)
			execve(cmd_data[0], cmd_data, env_array);
		else
		{
			exit_signal_by_result(result, cmd_data);
			return ;
		}
	}
	head_relative_path_list = make_relative_path(env_path, cmd_data[0]);
	valid_path = find_valid_path(head_relative_path_list);
	if (valid_path)
		execve((char *)valid_path->content, cmd_data, env_array);
	printf("bash: %s: command not found\n", cmd_data[0]);
	g_exit_signal = 127;
}
