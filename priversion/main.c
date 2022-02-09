/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:55:53 by kyukim            #+#    #+#             */
/*   Updated: 2022/02/09 14:32:20 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env(char *env[])
{
	int		index;
	int		lenth;
	t_list	*head;
	t_list	*current;
	t_list	*check;

	index = 0;
	lenth = 0;
	head = sh_lstnew(NULL);
	while (env[index] != NULL)
	{
		lenth = sh_strchr(env[index], '=') - env[index];
		current = sh_lstnew(NULL);
		current->content = sh_strchr(env[index], '=') + 1;
		current->key = sh_substr(env[index], 0, lenth);
		sh_lstadd_back(&head, current);
		index++;
	}
	check = head->next;
	while (check->next != NULL)
	{
		printf("%s : %s\n", (char *)check->key, (char *)check->content);
		check = check->next;
	}
	printf("%s\n", (char *)check->content);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char *env[])
{
	int		idx;
	int		temp;
	char	*str;
	char	*full_cmd;
	char	**cmds;
	t_info	*info;

	temp = argc;
	str = argv[0];
	idx = 0;
	cmds = NULL;
	init_info(&info);
	check_info(info);
	copy_env(env);
	while (1)
	{
		full_cmd = readline("> ");					//enter 쳤을 때 full_cmd 에 할당
		if (sh_strcmp(full_cmd, "exit") == 0)
			break ;
		else if (full_cmd)
		{
			printf("full_cmd : %s\n", full_cmd);
			tokenize_fullcmd(info, full_cmd);
		}
		else
			break ;
		add_history(full_cmd);
		free(full_cmd);
	}
	return (EXIT_SUCCESS);
}
