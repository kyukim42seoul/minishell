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

void	padding(int level)
{
	int	i;
	int	len;

	i = 0;
	len = level * 16;
	while (i < len)
	{
		printf(" ");
		i++;
	}
}

void	print_tree(t_tree *root, int level)
{
	int	index;

	index =0;
	if (root == NULL)
	{
		padding(level);
		printf("<NULL>\n");
		return ;
	}
	else
	{
		print_tree(root->right, level + 1);
		padding(level);
		if (root->data)
		{
			printf("<%d : ", root->type);
			while (root->data[index])
			{
				printf("\"%s\" ", root->data[index]);
				index++;
			}
			printf(">\n");
		}
		print_tree(root->left, level + 1);
	}
}
