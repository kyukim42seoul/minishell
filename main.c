/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:55:53 by kyukim            #+#    #+#             */
/*   Updated: 2022/02/04 19:09:21 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	copy_env(char *env[])
{
	int	index;
	int	lenth;
	t_list	*head;
	t_list	*current;
	t_list	*check;

	index = 0;
	lenth = 0;
	head = sh_lstnew(NULL);
	while (env[index] != NULL)
	{
		lenth = sh_strchr(env[index], '=') - env[index];
		current = sh_lstnew((void *)sh_strchr(env[index], '=') + 1);
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
	int	idx;
	int	temp;
	char	*str;
	char	*cmd;

	temp = argc;
	str = argv[0];
	idx = 0;
	copy_env(env);
	while (1)
	{
		cmd = readline("> ");	//enter 쳤을 때 cmd 에 할당
		if (sh_strcmp(cmd, "exit") == 0)
			break;
		else if (cmd)
			printf("cmd : %s\n", cmd);
		else
			break;
		add_history(cmd);
		free(cmd);
	}
	return (EXIT_SUCCESS);
}
