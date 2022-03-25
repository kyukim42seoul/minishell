/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:32 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/25 18:15:06 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtin_pwd(char **str)
{
	char	*s;

	if (*(++str))
	{
		if (((*str)[0] == '-' && (*str)[1] && (*str)[1] != '-')
			|| ((*str)[0] == '-' && (*str)[1] && (*str)[1] == '-' && (*str)[2]))
		{
			printf("bash: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n",
				(*str)[1]);
			exit_signal = 1;
			return ;
		}
	}
	s = getcwd(NULL, 0);
	ft_putstr_fd(s, 1);
	ft_putchar_fd('\n', 1);
	exit_signal = 0;
	free(s);
}
