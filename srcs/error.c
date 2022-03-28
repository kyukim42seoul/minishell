/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:41:32 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 22:28:29 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_one(char *cmd, int status)
{
	char	*error;

	error = NULL;
	if (status == 1)
	{
		error = ft_strjoin(ft_strjoin("bash: cd: ", cmd),
				": No such file or directory\n");
	}
	else if (status == 2)
	{
		error = ft_strjoin(ft_strjoin("bash: export: ", cmd),
				": not a valid identifier\n");
	}
	else if (status == 3)
	{
		error = ft_strjoin(ft_strjoin("env: illegal option -- ", cmd),
				"\nusage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
		error = ft_strjoin(error, "[name=value ...] [utility [argument ...]]\n");
	}
	else if (status == 4)
		error = strdup("bash: exit: too many arguments\n");
	write(2, error, ft_strlen(error));
	g_exit_signal = 1;
	free(error);
}

void	action_error(char *cmd, int status)
{
	char	*error;
	char	*start;

	error = NULL;
	start = ft_strjoin("bash: ", cmd);
	if (status == 127)
		error = ft_strjoin(start, ": command not found\n");
	else if (status == 126)
		error = ft_strjoin(start, ": is a directory\n");
	else if (status == 1270)
	{
		error = ft_strjoin(start, ":  No such file or directory\n");
		status = 127;
	}
	g_exit_signal = status;
	write(2, error, ft_strlen(error));
	free(error);
}
