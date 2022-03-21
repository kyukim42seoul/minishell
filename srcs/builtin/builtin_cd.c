#include "../proto.h"

void	change_pwd(t_info *info, char *old)
{
		int			flag;
		t_list	*check;

		check = info->e_head->next;
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

void	change_env(t_info *info)
{
	t_list *check;
	char *pwd;
	char *old;
	int flag;

	pwd = getcwd(NULL, 0);
	old = NULL;
	flag = 0;
	check = info->e_head->next;
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
		change_pwd(info, old);
	exit_signal = 0;
}

char	*get_env_value(t_list *head, char *key)
{
	t_list *check;

	check = head->next;
	while (check)
	{
		if (!ft_strncmp(check->key, key, ft_strlen(check->key)))
			return(ft_strdup(check->content));
		check = check->next;
	}
	return (NULL);
}

void	builtin_cd(t_info *info, char **str)
{
	char *path;
	int		i;

	i = 0;
	if (*(++str) == NULL || ((*str)[0] == '~' && !(*str)[1]))
		path = get_env_value(info->e_head, "HOME");
	else if (*str && (*str)[0] == '-' && !(*str)[1])
		path = get_env_value(info->e_head, "OLDPWD");
	else
		path = ft_strdup(*str);
	if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", *str);
		exit_signal = 1;
	}
	else
		change_env(info);
	free(path);
}