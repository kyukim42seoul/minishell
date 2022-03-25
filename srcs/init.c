/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:09:24 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/25 19:09:25 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_info(t_info **info)
{
	(*info) = malloc(sizeof(t_info));
	(*info)->debug = (t_debug *)malloc(sizeof(t_debug));
	(*info)->my_num = 0;
	(*info)->root = 0;
	return (EXIT_SUCCESS);
}
