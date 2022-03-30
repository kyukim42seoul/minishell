/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:05:43 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 20:09:52 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_pwd_path(char **cmd, char *mini, char **env)
{
	char	*new;

	new = ft_strjoin(getcwd(NULL, 0), ++(cmd[0]));
	if (!ft_strncmp(new, mini, (int)ft_strlen(new)))
		execve(new, cmd, env);
	free(new);
}

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
	while (cur)
	{
		result = check_path((char *)cur->content);
		if (result)
			return (cur);
		cur = cur->next;
	}
	if (result)
		return (cur);
	else
		return (NULL);
}
