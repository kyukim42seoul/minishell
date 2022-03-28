/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:59:56 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/28 16:46:28 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst_k	*ft_lstmap(t_lst_k *lst, void *(*f)(void *), void (*del)(void *))
{
	t_lst_k	*copy_lst;
	t_lst_k	*tem;
	t_lst_k	*tem_f;

	if (!lst)
		return (NULL);
	copy_lst = NULL;
	while (lst)
	{
		tem_f = f(lst->content);
		tem = ft_lstnew(tem_f);
		if (!tem)
		{
			ft_lstclear(&copy_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&copy_lst, tem);
		lst = lst->next;
	}
	return (copy_lst);
}
