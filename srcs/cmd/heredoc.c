/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:08:44 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/25 20:55:54 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	type_count(t_token *head, int type)
{
	int		count;
	t_token	*cur;

	count = 0;
	cur = 0;
	if (head == NULL)
		return (count);
	cur = head->next;
	while (cur)
	{
		if (cur->type == type)
			count++;
		cur = cur->next;
	}
	return (count);
}

char	*line_path_check(t_info *info, char *line)
{
	int		i;
	t_flag	flag;

	i = 0;
	flag.num = 0;
	while (line[i])
	{
		flag.type[0] = check_status_type(line[i]);
		if (flag.type[0] == PATH)
		{
			flag.len[flag.num] = characters_len(line, i + 1);
			flag.i_cur[flag.num] = i;
			flag.num++;
		}
		i++;
	}
	return (change_cmd_to_env(line, flag, info));
}

void	get_input(t_info *info, int index, char *eof)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line != NULL && ft_strncmp(line, eof, 1000))
		{
			line = line_path_check(info, line);
			write(info->heredoc[index].pip[1], line, ft_strlen(line));
			write(info->heredoc[index].pip[1], "\n", 1);
			free(line);
		}
		else
			break ;
	}
	if (line)
		free(line);
}

int	heredoc(t_info *info)
{
	int		index;
	int		child_number;
	int		count;
	t_token	*cur;

	index = 0;
	child_number = 0;
	count = type_count(info->t_head, LEFT_DOUBLE_REDI);
	info->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc) * (count + 1));
	info->heredoc[count].use_number = -1;
	cur = info->t_head->next;
	while (count > 0)
	{
		cur = find_heredoc(cur, &child_number);
		info->heredoc[index].use_number = child_number;
		pipe(info->heredoc[index].pip);
		get_input(info, index, cur->next->data);
		close(info->heredoc[index].pip[1]);
		cur = cur->next;
		index++;
		count--;
	}
	find_heredoc(cur, &child_number);
	return (EXIT_SUCCESS);
}
