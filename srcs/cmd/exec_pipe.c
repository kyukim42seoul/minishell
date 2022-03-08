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