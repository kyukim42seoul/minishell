/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:14 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 22:29:32 by kbaek            ###   ########.fr       */
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
	char	*error;

	error = NULL;
	if (*(++str))
	{
		if (((*str)[0] == '-' && (*str)[1] && (*str)[1] != '-')
			|| ((*str)[0] == '-' && (*str)[1] && (*str)[1] == '-' && (*str)[2]))
			error_one(&(*str)[1], 3);
		else
		{
			error = ft_strjoin(ft_strjoin("env: ", *str),
					": No such file or directory\n");
			write(2, error, ft_strlen(error));
			free(error);
			g_exit_signal = 127;
		}
		return ;
	}
	print_env_out(info->e_head);
}
