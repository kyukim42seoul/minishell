#include "proto.h"

void	list_insert(t_csh *csh, char *k, char *v)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		ft_free(csh);
	env->key = k;
	env->value = v;
	env->next = csh->env_head;
	csh->env_head = env;
	env = NULL;
}
