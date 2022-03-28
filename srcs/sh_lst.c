/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:10:34 by kyukim            #+#    #+#             */
/*   Updated: 2022/03/25 19:10:35 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*sh_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*sh_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	sh_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
		*lst = new;
	sh_lstlast(*lst)->next = new;
	new->next = NULL;
}

void	*find_content_from_key(t_list *env, char *key)
{
	t_list	*cur;

	cur = env->next;
	while (cur->next)
	{
		if (cur->key)
		{
			if (ft_strncmp((char *)cur->key, key, ft_strlen(key)) == 0)
				return (cur->content);
		}
		cur = cur->next;
	}
	if (cur->key)
	{
		if (ft_strncmp((char *)cur->key, key, ft_strlen(key)) == 0)
			return (cur->content);
	}
	return (NULL);
}

void	add_head(t_info *info, int type)
{
	t_token	*temp;

	temp = 0;
	if (info->t_head == NULL)
		return ;
	temp = kb_lstnew();
	temp->type = type;
	lstadd_front(&info->t_head, temp);
	info->t_head = temp;
}
