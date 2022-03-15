# include "../proto.h"

void	exec_cycle(t_tree *root, char *env)
{
	if (root == NULL)
		return ;
	if (root->type == PSREDIR)
	{
		if (root->left)
			redir_hub(root);
	}
	else if (root->type == PSBIN)
	{
		if (root->left)
			if (run_execve(root, env) == EXIT_FAILURE)
				printf("run_execve : %s\n", strerror(errno));
	}
	exec_cycle(root->left, env);
	exec_cycle(root->right, env);
}