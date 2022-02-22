#include "proto.h"

void	print_t_token(t_info *info)
{
	t_token	*check;

	check = info->t_head;
	if (check != NULL)
	{
		printf("\n\nnext 순서 -> \n");
		while (check->next != NULL)
		{
			printf("type = %d  data = |%s|\n", check->type, (char *)check->data);
			check = check->next;
		}
		printf("type = %d  data = |%s|\n", check->type, (char *)check->data);
		//printf("\n\nprev 반대 순서 -> \n");
		// check = kb_lstlast(info->t_head);
		// while (check->prev != NULL)
		// {
		// 	printf("type = %d  data = |%s|\n", check->type, (char *)check->data);
		// 	check = check->prev;
		// }
		// printf("type = %d  data = |%s|\n", check->type, (char *)check->data);
	}
}

void	print_env(t_info *info)
{
	t_list *check;

	check = info->head->next;
	while (check->next != NULL)
	{
		printf("%s=%s\n", (char *)check->key, (char *)check->content);
		check = check->next;
	}
	printf("%s=%s\n", (char *)check->key, (char *)check->content);
}
