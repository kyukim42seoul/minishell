/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:20 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/25 18:15:00 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_exit_arguments(t_info *info, char **str)
{
	if ((*(++str)) != NULL)
	{
		exit_signal = 1;
		printf("bash: exit: too many arguments\n");
	}
	else
	{
		if (info->root->right == NULL)
			printf("exit\n");
		exit(ft_atoi(*(--str)));
	}
}

void	builtin_exit(t_info *info, char **str)
{
	int	i;

	if (*(++str) == NULL)
	{
		if (info->root->right == NULL)
			printf("exit\n");
		exit(exit_signal);
	}
	i = 0;
	while ((*str)[i])
	{
		if (!ft_isdigit((*str)[i++]))
		{
			if (info->root->right == NULL)
				printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", *str);
			exit(255);
		}
	}
	check_exit_arguments(info, str);
}
