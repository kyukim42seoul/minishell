/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:08:52 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/28 18:42:04 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	right_redir(char *path)
{
	int		fd;

	fd = 0;
	if (path == NULL)
	{
		printf("RIGHT_REDIR : empty path\n");
		printf("%s\n", strerror(errno));
		return (-1);
	}
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd == -1)
	{
		printf("RIGHT_REDIR : fail open(%s)\n", path);
		printf("%s\n", strerror(errno));
		return (-1);
	}
	if (change_stdout(fd) == EXIT_FAILURE)
	{
		printf("%s\n", strerror(errno));
		return (-1);
	}
	return (EXIT_SUCCESS);
}

int	double_right_redir(char *path)
{
	int		fd;

	fd = 0;
	if (path == NULL)
	{
		printf("RIGHT_REDIR\n");
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0755);
	if (fd == -1)
	{
		printf("RIGHT_REDIR\n");
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (change_stdout(fd) == EXIT_FAILURE)
	{
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	left_redir(char *path)
{
	int		fd;

	fd = 0;
	if (path == NULL)
	{
		printf("RIGHT_REDIR\n");
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	fd = open(path, O_RDONLY, NULL);
	if (fd == -1)
	{
		printf("LEFT_REDIR\n");
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (change_stdin(fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
	각 자식 프로세스가 자기 번호(info->my_num) 보다 같거나 작은 use_number 를 가진 heredoce 을 건너뜀.
	자기 번호보다 큰 use_number 의 첫 heredoc 혹은 heredoc 배열 끝(use_number = -1)에 도착.
	자기 번호의 마지막 heredoc 으로 가야 하기때문에 index--;
	해당 heredoc[index] 에서 stdin 연결
*/

int	left_doulbe_redir(t_info *info, t_tree *root)
{
	int	index;

	index = 0;
	while (info->heredoc[index].use_number != root->my_number)
		index++;
	while (root->my_my > 0)
	{
		root->my_my--;
		index++;
	}
	change_stdin(info->heredoc[index].pip[0]);
	return (EXIT_SUCCESS);
}

void	redir_hub(t_info *info, t_tree *root)
{
	if (root->left->left->type == LEFT_REDI)
		left_redir(root->left->right->data[0]);
	else if (root->left->left->type == RIGHT_REDI)
		right_redir(root->left->right->data[0]);
	else if (root->left->left->type == RIGHT_DOUBLE_REDI)
		double_right_redir(root->left->right->data[0]);
	else if (root->left->left->type == LEFT_DOUBLE_REDI)
		left_doulbe_redir(info, root->left->left);
	return ;
}
