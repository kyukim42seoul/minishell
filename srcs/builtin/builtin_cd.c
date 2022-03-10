#include "../proto.h"

void	change_env(t_info *info)
{
	t_list *check;
	char *pwd;
	char *old;
	int flag;

	pwd = getcwd(NULL, 0);
	old = NULL;
	flag = 0;
	check = info->head;
	while (check)
	{
		if (!ft_strncmp(check->key, "PWD", ft_strlen(check->key)))
		{
			old = check->content;
			check->content = pwd;
			flag = 1;
			break ;
		}
		check = check->next;
	}
	if (flag == 0)
		env_add(info, "PWD", pwd);
	if (old != NULL)
	{
		check = info->head;
		flag = 0;
		while (check)
		{
			if (!ft_strncmp(check->key, "OLDPWD", ft_strlen(check->key)))
			{
				free(check->content);
				check->content = old;
				flag = 1;
				break ;
			}
			check = check->next;
		}
		if (flag == 0)
			env_add(info, "OLDPWD", old);
	}
}

char	*get_env_value(t_list *head, char *key)
{
	t_list *check;

	check = head;
	while (check)
	{
		if (!ft_strncmp(check->key, key, ft_strlen(check->key)))
			return(ft_strdup(check->content));
		check = check->next;
	}
	return (NULL);
}

void	builtin_cd(t_info *info, char **str, int *exit_signal)
{
	char *path;
	int		i;

	i = 0;
	if (*(++str) == NULL || ((*str)[0] == '~' && !(*str)[1]))
		path = get_env_value(info->head, "HOME");
	else if (*str && (*str)[0] == '-' && !(*str)[1])
		path = get_env_value(info->head, "OLDPWD");
	else
		path = ft_strdup(*str);
	if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", *str);
		*exit_signal = 1;
	}
	else
		change_env(info);
	free(path);
}