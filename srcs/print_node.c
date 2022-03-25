#include "proto.h"

void	print_t_token(t_info *info)
{
	t_token	*check;

	check = info->t_head;
	if (check != NULL)
	{
		printf("\n\nnext 순서 -> \n");
		while (check != NULL)
		{
			printf("type = %d  data = |%s|\n", check->type, (char *)check->data);
			check = check->next;
		}
		printf("\n\nprev 반대 순서 -> \n");
		check = kb_lstlast(info->t_head);
		while (check != NULL)
		{
			printf("type = %d  data = |%s|\n", check->type, (char *)check->data);
			check = check->prev;
		}
	}
}

void	print_env(t_info *info)
{
	t_list	*check;

	check = info->e_head->next;
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

	index = 0;
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
			printf("<%d | 1 = %d 2 = %d : ", root->type, root->my_number, \
					root->my_my);
			while (root->data[index])
			{
				printf("\"%s\"", root->data[index]);
				index++;
			}
			printf(">\n");
		}
		print_tree(root->left, level + 1);
	}
}
