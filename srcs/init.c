/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:09:24 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/28 19:25:03 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_info(t_info **info)
{
	(*info) = malloc(sizeof(t_info));
	(*info)->debug = (t_debug *)malloc(sizeof(t_debug));
	(*info)->debug->syntax_error = 0;
	(*info)->debug->error_point_data = 0;
	(*info)->my_num = 0;
	(*info)->root = 0;
	(*info)->minishell = ft_strjoin(getcwd(NULL, 0), "/minishell");
	return (EXIT_SUCCESS);
}
