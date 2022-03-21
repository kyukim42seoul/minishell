# include "../proto.h"

char	*take_env_value(t_list *head, char *key, int len)
{
	t_list	*env;

	env = head->next;
	//수정 이유 : 새그폴트
	//원인 : ft_strncmp() 는 NULL 방어가 없이 s1[index] 에 무조건 접근. env 에서 head 를 받으면 첫 (char *)env->key == NULL.
	while (env)
	{
		if(len == 0)
			break ;
		if (!ft_strncmp((char *)env->key, key, len))
			return (ft_strdup((char *)env->content));
		env = env->next;
	}
	return ("");
}

char *cmd_key_to_value(char *cmd, t_flag *flag, int i, char *vlaue)
{
	char	*start;
	char	*end;
	char	*temp;
	int		last_len;

	start = ft_substr(cmd, 0, flag->i_cur[i]);
	temp = ft_strjoin(start, vlaue);
	free(start);
	last_len = flag->i_cur[i] + flag->len[i] + 1;
	end = ft_substr(cmd, last_len, ft_strlen(cmd) - last_len);
	start = ft_strjoin(temp, end);
	free(temp);
	free(end);
	i++;
	while (i < flag->num)
	{
		flag->i_cur[i] = flag->i_cur[i] - (flag->len[i - 1] + 1 - ft_strlen(vlaue));
		i++;
	}
	return (start);
}

char *change_cmd_to_env(char *cmd, t_flag flag, t_info *info)
{
	char *str;
	char *env_key;
	char *env_value;
	int i;

	str = cmd;
	i = 0;
	while (i < flag.num)
	{
		if (flag.len[i] == 1 && str[flag.i_cur[i] + 1 ] == '?')
			env_value = ft_itoa(exit_signal);
		else
		{
			env_key = ft_substr(&str[flag.i_cur[i] + 1], 0, flag.len[i]);
			env_value = take_env_value(info->e_head, env_key, flag.len[i]);
		}
		str = cmd_key_to_value(str, &flag, i, env_value);
		i++;
	}
	return (str);
}