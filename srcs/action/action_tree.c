# include "../proto.h"

/*
아래와 같이 사용 될 예정
	main()
	{
		while (root->right)
		{
			exec_pipe();
			root = root->right;
		}
		return (0);
	}
*/

void	set_fd(int fd[2])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	exec_pipe(t_info *info, t_tree *root, int fd[2])
{
	pid_t	pid;

	if (root->right)
	{
		if (pipe(fd) < 0)
		{
			printf("exec_pipe : failed open pipe()\n");
			return ;
		}
	}
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		if (root->right)
			set_fd(fd);
		printf("It's child\n");
		root->right = NULL;
		print_tree(root, 0);
		single_tree(info, root);
		exit (0);
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

//전위 순회 루트->왼쪽->오른쪽 순서 
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

void	action_tree(t_info *info, int *exit_signal)
{
	t_tree	*cur_tree;
	int		result;
	int 	fd[2];
	pid_t	check;
	int		status;

	status = 0;
	cur_tree = info->root;
	if (!(cur_tree->right) && check_builtin(cur_tree))
	{
		result = single_tree(info, cur_tree->left);
		if (result < 0)
			printf("error\n");
	}
	else
	{
		while (cur_tree->right)
		{
			exec_pipe(info, cur_tree, fd);
			cur_tree = cur_tree->right;
		}
		exec_pipe(info, cur_tree, fd);
		check = wait(&status);
		printf("It's parent\n");
		// print_tree(info->root, 0);
		return ;
	}
	*exit_signal = 1;
}