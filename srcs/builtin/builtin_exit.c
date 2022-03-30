/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:20 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 22:10:07 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_exit_arguments(t_info *info, char **str)
{
	if ((*(++str)) != NULL)
		error_one(NULL, 4);
	else
	{
		if (info->root->right == NULL)
			printf("exit\n");
		exit(ft_atoi(*(--str)));
	}
}

void	builtin_exit(t_info *info, char **str)
{
	int		i;
	char	*error;

	error = NULL;
	if (*(++str) == NULL)
	{
		if (info->root->right == NULL)
			printf("exit\n");
		exit(g_exit_signal);
	}
	i = 0;
	while ((*str)[i])
	{
		if (!ft_isdigit((*str)[i++]))
		{
			if (info->root->right == NULL)
				printf("exit\n");
			error = ft_strjoin(ft_strjoin("bash: exit: ", *str),
					": numeric argument required\n");
			write(2, error, ft_strlen(error));
			exit(255);
		}
	}
	check_exit_arguments(info, str);
}
