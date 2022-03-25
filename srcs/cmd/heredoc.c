#include "../proto.h"

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
	int i;
	t_flag flag;

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

int	heredoc(t_info *info)
{
	int		index;
	int		child_count;
	int		child_number;
	int		count;
	char	*eof;
	char	*line;
	t_token	*cur;

	index = 0;
	child_number = 0;
	child_count = type_count(info->t_head, PIPE) + 1;
	count = type_count(info->t_head, LEFT_DOUBLE_REDI);
	info->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc) * (count + 1));
	cur = info->t_head->next;
	while (count > 0)
	{
		cur = find_heredoc(cur);
		eof = cur->next->data;
		pipe(info->heredoc[index].pip);
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
		close(info->heredoc[index].pip[1]);
		cur = cur->next;
		if (child_count -  (type_count(cur, PIPE) + 1) > 0)
		{
			child_count = type_count(cur, PIPE) + 1;
			child_number++;
		}
		info->heredoc[index].use_number = child_number;
		index++;
		count--;
	}
	return (EXIT_SUCCESS);
}
