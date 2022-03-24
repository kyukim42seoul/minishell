#include "proto.h"

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
