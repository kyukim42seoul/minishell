/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:41:32 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/29 14:53:09 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	stand_err(char *error, char *start)
{
	write(2, error, ft_strlen(error));
	g_exit_signal = 1;
	free(error);
	if (start)
		free(start);
}

void	error_one(char **cmd, int status)
{
	char	*error;
	char	*start;

	error = NULL;
	start = NULL;
	if (status == 1)
	{
		start = ft_strjoin("bash: cd: ", *cmd);
		error = ft_strjoin(start,
				": No such file or directory\n");
	}
	else if (status == 2)
	{
		start = ft_strjoin("bash: export: ", *cmd);
		error = ft_strjoin(start, ": not a valid identifier\n");
	}
	else if (status == 3)
	{
		start = ft_strjoin("env: illegal option -- ", *cmd);
		error = ft_strjoin(start, "\nusage: env [-iv] [-P utilpath] [-S string] [-u name]\
				\n	[name=value ...] [utility [argument ...]]\n");
	}
	else if (status == 4)
		error = strdup("bash: exit: too many arguments\n");
	stand_err(error, start);
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
