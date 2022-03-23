/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proto.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:46:33 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/23 20:00:43 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto.h"

int	quotation_check(char *s, int i)
{
	int	status;

	status = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			if (status == 0)
				status = 1;
			else if (status == 1)
				status = 0;
		}
		else if (s[i] == '\"')
		{
			if (status == 0)
				status = 2;
			else if (status == 2)
				status = 0;
		}
		i++;
		while (s[i] && (s[i] != '\"' && s[i] != '\''))
			i++;
	}
	return (status);
}

int	check_cmd(char *cmd)
{
	int	i;

	if (*cmd == '\0')
		return (1);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 32 || (cmd[i] >= 9 && cmd[i] <= 13))
			i++;
		else
			return (0);
	}
	return (1);
}

/*
	main 함수 설명
*/
int	main(int argc, char *argv[], char *env[])
{
	char	*full_cmd;
	t_info	*info;

	(void)argc;
	(void)argv;
	set_signal();
	init_info(&info);
	copy_env(info, env);
	info->origin_env = env;
	while (1)
	{
		full_cmd = readline("in> ");
		if (full_cmd == NULL)
		{
			printf("\033[1A");// 커서를 위로 한 줄 올린다.
			printf("\033[4C");// 커서를 4만큼 오른쪽으로 민다.
			printf("exit\n");
			exit (-1);
		}
		else if (!check_cmd(full_cmd) && !quotation_check(full_cmd, 0))
		{
			tokenize(full_cmd, info);
			add_head(info, PIPE);
			set_type(info->t_head);
			if (syntax_hub(info->t_head, info->debug) == EXIT_FAILURE && info->t_head != NULL)
				printf("syntax error\npoint : %s\ndata : %s\n", info->debug->syntax_error, (char *)info->debug->error_point_data);
			parse_tree(info);
			action(info, 0, 0);
			add_history(full_cmd);
			postorder_del_tree(info->root);
		}
		free(full_cmd);
		info->root = 0;
	}
	return (EXIT_SUCCESS);
}
