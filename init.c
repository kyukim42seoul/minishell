/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:13:17 by kyukim            #+#    #+#             */
/*   Updated: 2022/02/06 18:59:08 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_info(t_info **info)
{
	(*info) = (t_info *)malloc(sizeof(t_info));
	(*info)->cmd = 0;
	(*info)->pipe_flag = -1;
	(*info)->redirection_flag = -1;
	(*info)->double_shift_flag = -1;
	return (EXIT_SUCCESS);
}

int	init_cmd_s(t_cmd **cmd_s)
{
	(*cmd_s) = (t_cmd *)malloc(sizeof(t_cmd));
	(*cmd_s)->cmd = NULL;
	(*cmd_s)->option = NULL;
	(*cmd_s)->args = arg_new();
	(*cmd_s)->next = NULL;
	return (EXIT_SUCCESS);
}

int	check_info(t_info *info)
{
	printf("cmd, flag 1, 2, 3 = %d %d %d\n", info->pipe_flag, info->redirection_flag, info->double_shift_flag);
	return (EXIT_SUCCESS);
}