# include "../proto.h"

int	change_stdout(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("CHANGE_STDOUT : dup2 failed\n");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	change_stdin(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("CHANGE_STDIN : dup2 failed\n");
		return (EXIT_FAILURE);
	}
	printf("stdin changed\n");
	close(fd);
	printf("done change_stdin()\n");
	return (EXIT_SUCCESS);
}

int	right_redir(char *path)
{
	int		fd;

	fd = 0;
	if (path == NULL)
	{
		printf("RIGHT_REDIR : empty path\n");
		return (EXIT_FAILURE);
	};
	fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0755);
	if (fd == -1)
	{
		printf("RIGHT_REDIR : fail open(%s)\n", path);
		return (EXIT_FAILURE);
	};
	if (change_stdout(fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	double_right_redir(char *path)
{
	int		fd;

	fd = 0;
	if (path == NULL)
	{
		printf("RIGHT_REDIR : empty path\n");
		return (EXIT_FAILURE);
	}
	fd = open(path, O_WRONLY|O_CREAT|O_APPEND, 0755);
	if (fd == -1)
	{
		printf("RIGHT_REDIR : fail open(%s)\n", path);
		return (EXIT_FAILURE);
	}
	if (change_stdout(fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	left_redir(char *path)
{
	int		fd;

	fd = 0;
	if (path == NULL)
	{
		printf("RIGHT_REDIR : empty path\n");
		return (EXIT_FAILURE);
	};
	fd = open(path, O_RDONLY, NULL);
	if (fd == -1)
	{
		printf("LEFT_REDIR : fail open(%s)\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (change_stdin(fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("done left_redir\n");
	return (EXIT_SUCCESS);
}

void	redir_hub(t_tree *root)
{
	if (root->left->type == LEFT_REDI)
		left_redir(root->right->data[0]);
	else if (root->left->type == RIGHT_REDI)
		right_redir(root->right->data[0]);
	else if (root->left->type == RIGHT_DOUBLE_REDI)
		double_right_redir(root->right->data[0]);
	return ;
}
