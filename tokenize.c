/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:25:28 by kyukim            #+#    #+#             */
/*   Updated: 2022/02/06 19:07:05 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_fullcmd(t_cmd *cmd_s, char *full_cmd, char **cmds)
{
	char	*full_cmd_buf;
	char	*str_start;
	char	*str_end;
	int		value_index;
	t_arg	*arg_buf;

	full_cmd_buf = full_cmd;
	str_start = full_cmd_buf;
	str_end = NULL;
	cmds = NULL;
	value_index = 0;
	arg_buf = 0;
	while (sh_strchr(str_start, '"'))
	{
		if (sh_strchr(str_start, '"'))
		{
			str_start = sh_strchr(str_start, '"');
			if (sh_strchr(str_start + 1, '"'))
			{
				str_end = sh_strchr(str_start + 1, '"');
				arg_buf = arg_new();
				arg_buf->arg = sh_substr(full_cmd_buf, str_start - full_cmd_buf + 1, str_end - str_start - 1); //+1 -1 은 양쪽 끝의 따옴표를 지우기 위해
				printf("a\n");
				sh_lstadd_back((t_list **)cmd_s->args, (t_list *)arg_buf);
				printf("b\n");
				value_index++;
			}
			else
			{
				printf("syntex_error\n");
				return (EXIT_FAILURE);
			}
		}
	};
	return (EXIT_SUCCESS);
}