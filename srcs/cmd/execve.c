# include "../proto.h"

int	check_path(const char *path)
{
	int	result;
	struct stat *path_info;

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
	char	*merged_str;
	t_list	*head;
	t_list	*cur;

	index = 0;
	divided_env = ft_split(env_path, ':');
	head = sh_lstnew(NULL);
	while (divided_env[index])
	{
		buf = ft_strjoin(divided_env[index], "/");
		merged_str = ft_strjoin(buf, cmd);
		cur = sh_lstnew(merged_str);
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

/*
	절대경로(ex. /bin/cat)일 경우
		첫 check_path() 조건문에서 execve() 실행
	상대경로(ex. cat) 일 경우
		make_relative_path() 에서 $PATH 의 모든 경로와 cmd 를 조합 후 반환(t_list *head)
		find_valid_path() 에서 저장된 모든 경로(t_list *lst)를 확인하여 유효한 경로의 노드 반환(t_list *node)
		반환된 노드의 content 로 execve() 실행
*/
void	run_execve(char **cmd_data, char *env)
{
	t_list	*head_relative_path_list;
	t_list	*valid_path;
	int		result;

	head_relative_path_list = 0;
	if (cmd_data[0][0] == '/')
	{
		result = check_path(cmd_data[0]);
		if (result)
			execve(cmd_data[0], cmd_data, NULL);
		else
		{
			if (result == 2)
			{
				printf("bash: %s: is a directory\n", cmd_data[0]);
				exit_signal = 126;
			}
			else if (result == 0)
			{
				printf("bash: %s: No such file or directory\n",  cmd_data[0]);
				exit_signal = 127;
			}
			return ;
		}
	}
	head_relative_path_list = make_relative_path(env, cmd_data[0]);
	valid_path = find_valid_path(head_relative_path_list);
	printf("path = %s\n", (char *)valid_path->content);
	if (valid_path)
		execve((char *)valid_path->content, cmd_data, NULL);
	printf("bash: %s: command not found\n", cmd_data[0]);
	exit_signal = 127;
}