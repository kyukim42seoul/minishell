/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:09:24 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/28 21:49:18 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_info(t_info **info)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	(*info) = malloc(sizeof(t_info));
	(*info)->debug = (t_debug *)malloc(sizeof(t_debug));
	(*info)->debug->syntax_error = 0;
	(*info)->debug->error_point_data = 0;
	(*info)->root = 0;
	(*info)->minishell = ft_strjoin(buf, "/minishell");
	free(buf);
	return (EXIT_SUCCESS);
}
