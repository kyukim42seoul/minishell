// # include "../proto.h"

// /*
// 아래와 같이 사용 될 예정
// 	main()
// 	{
// 		while (root->right)
// 		{
// 			exec_pipe();
// 			root = root->right;
// 		}
// 		return (0);
// 	}
// */

// void	set_fd(t_info *info, t_tree *tree, int *in, int *out)
// {
// 	char temp[1];
// 	t_tree *t;

// 	if (info->pipe_flag != 0)
// 	{
// 		dup2(info->prein_pip, 0);
// 		// close(info->prein_pip);
// 		read(0, temp, 1);
// 		// printf("oh yeah == %s\n", temp);
// 		write(1, temp, 1);
// 		//write(1, "___", 3);
// 	}
// 	if (tree->right)
// 	{
// 		write(1, "\nok\n", 3);
// 		dup2(*out, 1);
// 		info->pipe_flag = 1;
// 		close(*in);
// 		close(*out);
// 	}
// 	t = tree_search_type(tree, 17);
// 	write(1, t->left->data[0], 1);
// }

// void	preorder(t_info *info, t_tree *tree)
// {
// 	int i = 0;

// 	if ((tree->type >= LEFT_REDI) && (tree->type <= RIGHT_DOUBLE_REDI))
// 		printf("type redi\n\n");
// 	else if (tree->type == CMD)
// 		implement_cmd(info, tree->data, &i);
	
// }

// //전위 순회 루트->왼쪽->오른쪽 순서 
// void		PreorderTraverse(t_info *info, t_tree *tree, VisitFuncPtr action)
// {
// 	if (tree == NULL)
// 		return ;
// 	action(info, tree);
// 	PreorderTraverse(info, tree->left, action);
// 	PreorderTraverse(info, tree->right, action);
// }

// int single_tree(t_info *info, t_tree *tree)
// {
	
// 	PreorderTraverse(info, tree, preorder);
// 	info->double_shift_flag = 0;
// 	return (1);
// }

// int	check_builtin(t_tree *tree)
// {
// 	t_tree	*find;
// 	int 	len;

// 	find = tree_search_type(tree, PSBIN);
// 	len = (int)ft_strlen(find->left->data[0]);
// 	if (!ft_strncmp(find->left->data[0], "echo", len) ||
// 		!ft_strncmp(find->left->data[0], "cd", len) ||
// 		!ft_strncmp(find->left->data[0], "pwd", len) ||
// 		!ft_strncmp(find->left->data[0], "env", len) ||
// 		!ft_strncmp(find->left->data[0], "export", len) ||
// 		!ft_strncmp(find->left->data[0], "unset", len) ||
// 		!ft_strncmp(find->left->data[0], "exit", len))
// 		return (1);
// 	return(0);
// }
// void	close_dup(int *stin, int *stout)
// {
// 	dup2(*stin, 0);
// 	dup2(*stout, 1);
// 	close(*stin);
// 	close(*stout);
// 	// close(info->prein_pip);
// }
// void	exec_pipe(t_info *info, t_tree *root)
// {
// 	pid_t	pid;
// 	int stdin_dup;
// 	int stdout_dup;
// 	int fd[2];

// 	stdin_dup = dup(0);
// 	stdout_dup = dup(1);
// 	if (root->right)
// 	{
// 		if (pipe(fd) < 0)
// 		{
// 			printf("exec_pipe : failed open pipe()\n");
// 			return ;
// 		}
// 		printf("fd[0] = %d\n", fd[0]);
// 	}
// 	pid = fork();
// 	if (pid < 0)
// 		return ;
// 	else if (pid == 0)
// 	{
// 		//set_fd(info, root, &fd[0], &fd[1]);
// 		if (info->pipe_flag != 0)
// 		{
// 			dup2(info->prein_pip, 0);
// 			close(info->prein_pip);
// 		}
// 		close(fd[0]);
// 		close(fd[1]);
// 		if (root->right)
// 		{
// 			write(1, "\n", 1);
			
// 		}
		
		
		
// 	char temp[1];
// 	t_tree *t;

// 	if (info->pipe_flag != 0)
// 	{
// 		dup2(info->prein_pip, 0);
// 		close(info->prein_pip);
// 		close(fd[1]);
// 		read(0, temp, 1);
// 		// printf("oh yeah == %s\n", temp);
// 		write(1, temp, 1);
// 		//write(1, "___", 3);
// 	}
// 	if (tree->right)
// 	{
// 		write(1, "\nok\n", 3);
// 		dup2(*out, 1);
// 		info->pipe_flag = 1;
// 		close(*in);
// 		close(*out);
// 	}
// 	t = tree_search_type(tree, 17);
// 	write(1, t->left->data[0], 1);


// 		// if (root->right)
// 		// {
// 		// 	set_fd(info, fd);
// 		// 	read(0, temp, 11);
// 		// 	printf("%s\n", temp);
// 		// }
// 		// printf("It's child\n");
// 		root->right = NULL;
// 		// print_tree(root, 0);
	
// 		// tree_traverse(info,);
// 		single_tree(info, root);
// 		close_dup(&stdin_dup, &stdout_dup);
// 		exit (0);
// 	}
// 	else if (root->right)
// 	{
// 		printf("pd %d\n", fd[0]);
// 		info->prein_pip = dup(fd[0]);
// 		printf("prein %d\n", info->prein_pip);
// 	 	// dup2(fd[0], info->prein_pip);
// 		close(fd[0]);
// 	}
// }
// void	action_tree(t_info *info, int *exit_signal)
// {
// 	t_tree	*cur_tree;
// 	int		result;
// 	pid_t	check;
// 	int		status;

// 	status = 0;
// 	check = 0;
// 	cur_tree = info->root;
// 	if (!(cur_tree->right) && check_builtin(cur_tree))
// 	{
// 		result = single_tree(info, cur_tree->left);
// 		if (result < 0)
// 			printf("error\n");
// 	}
// 	else
// 	{
// 		while (cur_tree->right)
// 		{
// 			exec_pipe(info, cur_tree);
// 			cur_tree = cur_tree->right;
// 			printf("pre = %d\n", info->prein_pip);
// 		}
// 		exec_pipe(info, cur_tree);
// 		while ((check = wait(&status)) > 0);
// 		// while (check <= 0)
// 		// 	check = waitpid(-1, &status, 0);
// 		printf("It's parent\n");
// 		print_tree(info->root, 0);
// 		return ;
// 	}
// 	*exit_signal = 1;
// }
