# include "../proto.h"

void	PreorderTraverse(t_info *info, t_tree *tree)
{
	int	exit_signal;

	exit_signal = 0;
	if (tree == NULL)
		return ;
	if (tree->type == PSIO)
	{
		if (tree->left)
			redir_hub(tree);
	}
	else if (tree->type == CMD)
		implement_cmd(info, tree->data);
	PreorderTraverse(info, tree->left);
	PreorderTraverse(info, tree->right);
}

int	single_tree(t_info *info, t_tree *tree)
{
	PreorderTraverse(info, tree);
	info->double_shift_flag = 0;
	return (1);
}

int	check_builtin(t_tree *tree)
{
	t_tree	*find;
	int 	len;

	find = tree_search_type(tree, PSBIN);
	len = (int)ft_strlen(find->left->data[0]);
	if (!ft_strncmp(find->left->data[0], "echo", len) ||
		!ft_strncmp(find->left->data[0], "cd", len) ||
		!ft_strncmp(find->left->data[0], "pwd", len) ||
		!ft_strncmp(find->left->data[0], "env", len) ||
		!ft_strncmp(find->left->data[0], "export", len) ||
		!ft_strncmp(find->left->data[0], "unset", len) ||
		!ft_strncmp(find->left->data[0], "exit", len))
		return (1);
	return(0);
}

void	pipe_setting(t_tree *root)
{
	if (root->type != PSPIPE && root->prepip > -1)
	{
		dup2(root->prepip, 0);
		close(root->prepip);
	}
	if (root->right)
		dup2(root->pip[1], 1);
	close(root->pip[0]);
	close(root->pip[1]);
}

void	excute_tree(t_info *info, t_tree *root)
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
		exit(1);
	}
}

void	action(t_info *info)
{
	t_tree	*cur_tree;
	int		result;
	pid_t	check;
	int		status;
	int 	fd[2];

	status = 0;
	check = 0;
	cur_tree = info->root;
	if (!(cur_tree->right) && check_builtin(cur_tree))
	{
		result = single_tree(info, cur_tree->left);
		if (result < 0)
			printf("error\n");
	}
	else
	{
		while (cur_tree)
		{
			fd[0] = dup(STDIN_FILENO);
			fd[1] = dup(STDOUT_FILENO);
			if (cur_tree->right)
			{
				pipe(cur_tree->pip);
				cur_tree->right->prepip = dup(cur_tree->pip[0]);
				close(cur_tree->pip[0]);
			}
			excute_tree(info, cur_tree);
			dup2(fd[0], STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			cur_tree = cur_tree->right;
		}
		while ((check = wait(&status)) > 0);
		exit_signal = WEXITSTATUS(status);
		return ;
	}
}

