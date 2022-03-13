# include "../proto.h"

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

void	set_pip(t_tree *root)
{
	int temp[2];
	t_tree *t;

	if (root->type != PSPIPE && root->prepip > -1)
	{
		dup2(root->prepip, 0);
		close(root->prepip);
		read(0, temp, 2);
		write(1, "pre = ", 6);
		write(1, temp, 2);
	}
	if (root->right)
		dup2(root->pip[1], 1);
	t = tree_search_type(root, 17);
	write(1, t->left->data[0], 2);
	close(root->pip[0]);
	close(root->pip[1]);
}

void	excute_tree(t_tree *root)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	 exit(1);
	else if (pid == 0)
	{
		set_pip(root);
		root->right = NULL;
		while (1);
		exit(1);
	}
}


void	preorder(t_info *info, t_tree *tree)
{
	int i = 0;

	if ((tree->type >= LEFT_REDI) && (tree->type <= RIGHT_DOUBLE_REDI))
		printf("type redi\n\n");
	else if (tree->type == CMD)
		implement_cmd(info, tree->data, &i);
	
}
void		PreorderTraverse(t_info *info, t_tree *tree, VisitFuncPtr action)
{
	if (tree == NULL)
		return ;
	action(info, tree);
	PreorderTraverse(info, tree->left, action);
	PreorderTraverse(info, tree->right, action);
}

int single_tree(t_info *info, t_tree *tree)
{
	
	PreorderTraverse(info, tree, preorder);
	info->double_shift_flag = 0;
	return (1);
}
void	action(t_info *info, int *exit_signal)
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
			excute_tree(cur_tree);
			dup2(fd[0], STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			cur_tree = cur_tree->right;
		}
		while ((check = wait(&status)) > 0);
		// while (check <= 0)
		// 	check = waitpid(-1, &status, 0);
		//print_tree(info->root, 0);
		return ;
	}
	*exit_signal = 1;
}