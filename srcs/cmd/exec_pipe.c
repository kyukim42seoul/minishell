# include "../proto.h"

/*
	자식 프로세스가 $PATH 를 쓸 수 있도록 char *env 세팅 후 fork()
*/
void	exec_pipe(t_tree *root, t_list *env_head)
{
	pid_t	pid;
	char	*env;

	env = (char *)find_content_from_key(env_head, "PATH");
	pid = fork();
	if (pid == 0)
	{
		printf("I'm child\n");
		root->right = NULL;
		exec_cycle(root, env);
		exit(EXIT_SUCCESS);
	}
}