/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmd_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:20:51 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/25 18:52:32 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*take_env_value(t_list *head, char *key)
{
	t_list	*env;

	env = head->next;
	while (env)
	{
		if (!ft_strncmp((char *)env->key, key, ft_strlen(env->key)))
			return (ft_strdup((char *)env->content));
		env = env->next;
	}
	return ("");
}

char	*cmd_key_to_value(char *cmd, t_flag *flag, int i, char *v)
{
	char	*start;
	char	*end;
	char	*temp;
	int		last_len;

	start = ft_substr(cmd, 0, flag->i_cur[i]);
	temp = ft_strjoin(start, v);
	free(start);
	last_len = flag->i_cur[i] + flag->len[i] + 1;
	end = ft_substr(cmd, last_len, ft_strlen(cmd) - last_len);
	start = ft_strjoin(temp, end);
	free(temp);
	free(end);
	i++;
	while (i < flag->num)
	{
		flag->i_cur[i] = flag->i_cur[i] - (flag->len[i - 1] + 1 - ft_strlen(v));
		i++;
	}
	return (start);
}

char	*change_cmd_to_env(char *cmd, t_flag flag, t_info *info)
{
	char	*str;
	char	*env_key;
	char	*env_value;
	int		i;

	str = cmd;
	i = 0;
	while (i < flag.num)
	{
		if (flag.len[i] == 1 && str[flag.i_cur[i] + 1 ] == '?')
			env_value = ft_itoa(g_exit_signal);
		else
		{
			env_key = ft_substr(&str[flag.i_cur[i] + 1], 0, flag.len[i]);
			env_value = take_env_value(info->e_head, env_key);
		}
		str = cmd_key_to_value(str, &flag, i, env_value);
		i++;
	}
	return (str);
}
