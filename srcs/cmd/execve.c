/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:08:40 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/28 21:20:54 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_signal_by_result(int result, char **cmd_data)
{
	if (result == 2)
		action_error(cmd_data[0], 126);
	else if (result == 0)
		action_error(cmd_data[0], 1270);
}

void	run_execve(char **cmd, char *env_path, char **env, char *mini)
{
	t_list	*head_relative_path_list;
	t_list	*valid_path;
	int		result;

	if (env_path)
	{
		head_relative_path_list = 0;
		if (cmd[0][0] == '/')
		{
			result = check_path(cmd[0]);
			if (result)
				execve(cmd[0], cmd, env);
			else
			{
				exit_signal_by_result(result, cmd);
				return ;
			}
		}
		else if (cmd[0][0] == '.' && cmd[0][1] && cmd[0][1] == '/')
			find_pwd_path(cmd, mini, env);
		head_relative_path_list = make_relative_path(env_path, cmd[0]);
		valid_path = find_valid_path(head_relative_path_list);
		if (valid_path)
			execve((char *)valid_path->content, cmd, env);
	}
}
