/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:14 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/25 18:35:40 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env_out(t_list *env)
{
	t_list	*check;

	check = env;
	while (check != NULL)
	{
		if (check->content != NULL)
		{
			ft_putstr_fd((char *)check->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd((char *)check->content, 1);
			ft_putchar_fd('\n', 1);
		}
		check = check->next;
	}
	g_exit_signal = 0;
}

void	builtin_env(t_info *info, char **str)
{
	if (*(++str))
	{
		if (((*str)[0] == '-' && (*str)[1] && (*str)[1] != '-')
			|| ((*str)[0] == '-' && (*str)[1] && (*str)[1] == '-' && (*str)[2]))
		{
			printf("env: illegal option -- %c\n", (*str)[1]);
			printf("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
			printf("            [name=value ...] [utility [argument ...]]\n");
			g_exit_signal = 1;
		}
		else
		{
			printf("env: %s: No such file or directory\n", *str);
			g_exit_signal = 127;
		}
		return ;
	}
	print_env_out(info->e_head);
}
