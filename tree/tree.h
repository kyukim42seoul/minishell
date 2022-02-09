#ifndef TREE_H
# define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_tree
{
	int				value;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

#endif
