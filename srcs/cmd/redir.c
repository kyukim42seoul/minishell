#include "../../include/minishell.h"

int	change_stdout(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("CHANGE_STDOUT\n");
		printf("%s\n", strerror(errno));
		return (-1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	change_stdin(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("CHANGE_STDIN\n");
		printf("%s\n", strerror(errno));
		return (-1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	right_redir(char *path)
{
	int		fd;

	fd = 0;
	if (path == NULL)
	{
		printf("RIGHT_REDIR : empty path\n");
		printf("%s\n", strerror(errno));
		return (-1);
	};
	fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0755);
	if (fd == -1)
	{
		printf("RIGHT_REDIR : fail open(%s)\n", path);
		printf("%s\n", strerror(errno));
		return (-1);
	};
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
	fd = open(path, O_WRONLY|O_CREAT|O_APPEND, 0755);
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
	};
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

int	left_doulbe_redir(t_info *info, t_tree *root)
{
	int	index;
	int i;

	index = 0;
	i = 0;
	while (root->my_number != info->heredoc[index].use_number)
		index++;
	if (root->my_number == info->heredoc[index].use_number)
	{
		while (root->my_my > i++)
			index++;
		change_stdin(info->heredoc[index].pip[0]);
	}
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
