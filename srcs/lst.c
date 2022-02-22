#include "proto.h"

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

t_token	*kb_lstnew(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*kb_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_token	*lstfront(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}

void	lstadd_front(t_token **lst, t_token *new)
{
	t_token	*front_node;

	front_node = 0;
	if (*lst == NULL)
		*lst = new;
	front_node = lstfront(*lst);
	front_node->prev = new;
	new->next = front_node;
	new->prev = NULL;
}
