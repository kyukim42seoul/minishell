#include "tree.h"

t_tree	*make_tree(void)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	new->left = NULL;
	new->right = NULL;
	return (new);
}

int	main()
{
	t_tree *root;

	root = make_tree();
	return (0);
}
