/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:13:17 by kyukim            #+#    #+#             */
/*   Updated: 2022/02/07 13:02:54 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_info(t_info **info)
{
	(*info) = malloc(sizeof(t_info));
	(*info)->cmd = 0;
	(*info)->pipe_flag = -1;
	(*info)->redirection_flag = -1;
	(*info)->double_shift_flag = -1;
	return (EXIT_SUCCESS);
}

int	init_mark(t_mark **mark)
{
	(*mark) = malloc(sizeof(t_mark));
	(*mark)->double_quote = 0;
	(*mark)->quote = 0;
	(*mark)->space = 0;
	(*mark)->l_double_shift = 0;
	(*mark)->r_double_shift = 0;
	(*mark)->l_shift = 0;
	(*mark)->r_shift = 0;
	(*mark)->pipe = 0;
	(*mark)->option = 0;
	return (EXIT_SUCCESS);
}

int	check_info(t_info *info)
{
	printf("cmd, flag 1, 2, 3 = %d %d %d\n", info->pipe_flag, info->redirection_flag, info->double_shift_flag);
	return (EXIT_SUCCESS);
}
