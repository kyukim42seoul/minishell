/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:25:28 by kyukim            #+#    #+#             */
/*   Updated: 2022/02/07 13:59:34 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mark_syntex(t_mark *mark)
{
	if (mark->double_quote % 2)
	{
		printf("wait more input : double qutes\n");
		return (2);
	}
	else if (mark->quote % 2)
	{
		printf("wait more input : qutes\n");
		return (2);
	}
	else if (mark->l_shift > 1)
	{
		printf("syntex_error : l shift\n");
		return (EXIT_FAILURE);
	}
	else if (mark->r_shift > 1)
	{
		printf("syntex_error : r shift\n");
		return (EXIT_FAILURE);
	}
	else if (mark->l_double_shift > 1)
	{
		printf("syntex_error : l double shift\n");
		return (EXIT_FAILURE);
	}
	else if (mark->r_double_shift > 1)
	{
		printf("syntex_error : r double shift\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	count_marks(t_mark *mark, char *full_cmd)
{
	int	index;
	int	syntex;

	index = 0;
	syntex = 0;
	while (full_cmd[index])
	{
		if (full_cmd[index] == '"')
			mark->double_quote++;
		else if (full_cmd[index] == 39)	//''' 이게 안 먹혀서 임시로 아스키 코드 사용
			mark->quote++;
		else if (full_cmd[index] == ' ')
			mark->space = 1;
		else if (full_cmd[index] == '<')
		{
			if (full_cmd[index] == '<' && full_cmd[index + 1] == '<')
			{
				mark->l_double_shift++;
				index++;
			}
			else
				mark->l_shift++;
		}
		else if (full_cmd[index] == '>')
		{
			if (full_cmd[index] == '>' && full_cmd[index + 1] == '>')
			{
				mark->r_double_shift++;
				index++;
			}
			else
				mark->r_shift++;
		}
		else if (full_cmd[index] == ':')
			mark->pipe++;
		else if (full_cmd[index] == '-')
			mark->option++;
		index++;
	}
	syntex = mark_syntex(mark);
	if (syntex == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (syntex == 2)
		return (2);
	else
		return (EXIT_SUCCESS);
}

int	tokenize_fullcmd(t_info *info, char *full_cmd)
{
	static t_mark	*mark;
	t_info	*temp;
	char	*full_cmd_buf;
	int		mark_syntex;
//	char	*str_start;
//	char	*str_end;

	temp = info;
	if (mark == NULL)
		init_mark(&mark);
	full_cmd_buf = full_cmd;
//	str_start = full_cmd_buf;
//	str_end = NULL;
	mark_syntex = count_marks(mark, full_cmd);
	if (mark_syntex == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (mark_syntex == 2)
		return (2);
	printf("Marks : dq %d q %d sp %d lsh %d rsh %d ldsh %d rdsh %d pipe %d option %d\n", \
	mark->double_quote, mark->quote, mark->space, mark->l_shift, mark->r_shift, mark->l_double_shift, mark->r_double_shift, mark->pipe, mark->option);
	init_mark(&mark);

/*	while (sh_strchr(str_start, '"'))
	{
		if (sh_strchr(str_start, '"'))
		{
			str_start = sh_strchr(str_start, '"');
			if (sh_strchr(str_start + 1, '"'))
			{
				str_end = sh_strchr(str_start + 1, '"');
				arg_buf->arg = sh_substr(full_cmd_buf, str_start - full_cmd_buf + 1, str_end - str_start - 1); //+1 -1 은 양쪽 끝의 따옴표를 지우기 위해
				sh_lstadd_back((t_list **)cmd_s->args, (t_list *)arg_buf);
			}
			else
			{
				printf("syntex_error\n");
				return (EXIT_FAILURE);
			}
		}
	};*/

	return (EXIT_SUCCESS);
}