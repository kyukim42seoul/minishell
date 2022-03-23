/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:03:25 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/23 17:15:07 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../proto.h"

void	pipe_setting(t_tree *root)
{
	if (root->type != PSPIPE && root->prepip > -1)
	{
		dup2(root->prepip, 0);
		close(root->prepip);
	}
	if (root->right)
	{
		dup2(root->pip[1], 1);
		close(root->pip[0]);
		close(root->pip[1]);
	}
}

void	fork_tree(t_info *info, t_tree *root, int *in, int *out)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		pipe_setting(root);
		root->right = NULL;
		single_tree(info, root);
		exit(exit_signal);
	}
	else
	{
		if (root->right)
		{
			close(root->pip[0]);
			close(root->pip[1]);
		}
		dup2(*in, STDIN_FILENO);
		dup2(*out, STDOUT_FILENO);
		close(*in);
		close(*out);
	}	
}

void	child_exit_signal(int status)
{
	while (1)
	{
		if (wait(&status) < 0)
			break ;
	}
	if (exit_signal == SIGINT_WITH_FORK)
		exit_signal = 130;
	else if (exit_signal == SIGQUIT_WITH_FORK)
		exit_signal = 131;
	else
		exit_signal = WEXITSTATUS(status);
}

void	action(t_info *info, int in, int out)
{
	t_tree	*cur_tree;
	int		status;

	status = 0;
	cur_tree = info->root;
	if (!(cur_tree->right) && check_builtin(cur_tree))
		single_tree(info, cur_tree->left);
	else
	{
		while (cur_tree)
		{
			in = dup(STDIN_FILENO);
			out = dup(STDOUT_FILENO);
			if (cur_tree->right)
			{
				pipe(cur_tree->pip);
				cur_tree->right->prepip = dup(cur_tree->pip[0]);
				close(cur_tree->pip[0]);
			}
			fork_tree(info, cur_tree, &in, &out);
			cur_tree = cur_tree->right;
		}
		child_exit_signal(status);
	}
}
