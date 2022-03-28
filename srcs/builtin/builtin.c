/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:44 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 20:59:17 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtin(t_tree *tree)
{
	t_tree	*find;
	int		len;

	find = tree_search_type(tree, PSBIN);
	if (find->left == NULL)
		return (1);
	len = (int)ft_strlen(find->left->data[0]);
	if (!ft_strncmp(find->left->data[0], "echo", len)
		|| !ft_strncmp(find->left->data[0], "cd", len)
		|| !ft_strncmp(find->left->data[0], "pwd", len)
		|| !ft_strncmp(find->left->data[0], "env", len)
		|| !ft_strncmp(find->left->data[0], "export", len)
		|| !ft_strncmp(find->left->data[0], "unset", len)
		|| !ft_strncmp(find->left->data[0], "exit", len))
		return (1);
	return (0);
}

void	env_add(t_info *info, char *key, char *content)
{
	t_list	*check;

	check = sh_lstnew(NULL);
	check->type = O_ENV;
	check->content = content;
	check->key = key;
	sh_lstadd_back(&info->e_head, check);
}

int	str_len(char **str)
{
	int		len;
	char	**temp;

	len = 0;
	temp = str;
	while (*temp)
	{
		len++;
		temp++;
	}
	return (len);
}

void	chekc_before_error_ms()
{
    ssize_t nr;
	char buf[255];
	
    nr = read(0, buf, 255);
    if(nr == -1) 
	{
        fprintf(stderr, "Failed to read file.\n");
    	exit(0);
    }
    else 
		printf("%s\n", buf);

}

void	implement_cmd(t_info *info, char **cmd)
{
	char	*env_path;
	char	*error;

	env_path = 0;
	if (!ft_strncmp("env", cmd[0], 4))
		builtin_env(info, cmd);
	else if (!ft_strncmp("export", cmd[0], 7))
		builtin_export(info, cmd);
	else if (!ft_strncmp("unset", cmd[0], 6))
		builtin_unset(info, cmd);
	else if (!ft_strncmp("pwd", cmd[0], 4))
		builtin_pwd(cmd);
	else if (!ft_strncmp("cd", cmd[0], 3))
		builtin_cd(info, cmd);
	else if (!ft_strncmp("echo", cmd[0], 5))
		builtin_echo(cmd);
	else if (!ft_strncmp("exit", cmd[0], 5))
		builtin_exit(info, cmd);
	else
	{
		env_path = (char *)find_content_from_key(info->e_head, "PATH");
		run_execve(cmd, env_path, info->env_array, info->minishell);
		error = ft_strjoin(ft_strjoin("bash: ", cmd[0]), ": command not found\n");
		write(2, error, ft_strlen(error));
		g_exit_signal = 127;
		free(error);
	}
}
