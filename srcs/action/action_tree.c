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

void	exec_pipe(t_tree *root)
{
//	int		fd[2];
	int		status;
	pid_t	pid;
	pid_t	check;

	check = 0;
/*	if (pipe(fd) < 0)
	{
		printf("exec_pipe : failed open pipe()\n");
		return ;
	}*/
	pid = fork();
	if (pid == 0)
	{
		root->right = NULL;
		printf("It's child\n");
		print_tree(root, 0);
		return ;
	}
	else
	{
		while (check <= 0)
		{
			check = wait(&status);
		}
		printf("It's parent\n");
		print_tree(root, 0);
		return ;
	}
}
//전위 순회 루트->왼쪽->오른쪽 순서 
void		PreorderTraverse(t_tree *bt, VisitFuncPtr action)
{
	if (bt == NULL)
		return ;
	action(bt->data);
	PreorderTraverse(bt->left, action);
	PreorderTraverse(bt->right, action);
}

int single_tree(t_info *info, t_tree *tree, int fds[2])
{

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
	int 	fds[2];
	int		result;

	pipe(fds);
	cur_tree = info->root;
	if (!(cur_tree->right) && check_builtin(cur_tree))
	{
		result = single_tree(info, cur_tree->left, fds);
		if (result < 0)
			printf("error\n");
	}
	else
	{
		while (cur_tree->right)
		{
			exec_pipe(cur_tree);
			cur_tree = cur_tree->right;
		}
		exec_pipe(cur_tree);
	}
	*exit_signal = 1;
}