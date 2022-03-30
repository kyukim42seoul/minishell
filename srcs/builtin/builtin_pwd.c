/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:32 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 22:29:54 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_pwd(char **str)
{
	char	*s;
	char	*error;

	error = NULL;
	if (*(++str))
	{
		if (((*str)[0] == '-' && (*str)[1] && (*str)[1] != '-')
			|| ((*str)[0] == '-' && (*str)[1] && (*str)[1] == '-' && (*str)[2]))
		{
			error = ft_strjoin(ft_strjoin("bash: pwd: -", &(*str)[1]),
					": invalid option\npwd: usage: pwd [-LP]\n");
			write(2, error, ft_strlen(error));
			g_exit_signal = 1;
			free(error);
			return ;
		}
	}
	s = getcwd(NULL, 0);
	ft_putstr_fd(s, 1);
	ft_putchar_fd('\n', 1);
	g_exit_signal = 0;
	free(s);
}
