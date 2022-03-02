# include "proto.h"

t_tree	*dup_node(t_token *token)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	
	new->type = token->type;
	new->data = token->data;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_tree	*type_only_node(int type)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	return (new);
}


void	left_subtree(t_tree *root, t_tree *sub)
{
	if (root->left != NULL)
		root->left = NULL;
	root->left = sub;
}

void	right_subtree(t_tree *root, t_tree *sub)
{
	if (root->right != NULL)
		root->right = NULL;
	root->right = sub;
}

t_tree	*tree_pipe(t_tree *root, t_token *token)
{
	t_tree	*buf;
	t_tree	*cur_root;

	buf = 0;
	cur_root = root;
	if (root == 0)
	{
		buf = type_only_node(2);				//PIPE in .h
		buf->data = "|";
		buf->left = type_only_node(4);			//CMD
		buf->left->left = type_only_node(3);	//IO
		buf->left->left->left = type_only_node(2);	//REDIR
		buf->left->right = type_only_node(1);	//SIMPLE_CMD
		root = buf;
	}
	else
	{
		while (cur_root->right != NULL)
			cur_root = cur_root->right;
		buf = dup_node(token);
		buf->left = type_only_node(4);			//CMD
		buf->left->left = type_only_node(3);	//IO
		buf->left->left->left = type_only_node(2);	//REDIR
		buf->left->right = type_only_node(1);	//SIMPLE_CMD
		cur_root->right = buf;
	}
	return (root);
}

t_tree	*tree_search_type(t_tree *root, int type)
{
	t_tree	*buf;

	buf = 0;
	if (root == NULL)
		return (NULL);
	if (root->type == type)
	{
		buf = root;
		return (buf);
	}
	buf = tree_search_type(root->left, type);
	if (buf)
		return (buf);
	buf = tree_search_type(root->right, type);
	if (buf)
		return (buf);
	return (buf);
}

int	check_io_leaf(t_tree *io_node)
{
	if (io_node->left->left)
		return (1);
	else
		return (0);
}

t_tree	*tree_io(t_tree *root, t_token *token)
{
	t_tree	*buf;
	t_tree	*dup_token;
	t_tree	*cmd_node;
	t_tree	*io_node;
	t_tree	*cur_root;

	buf = 0;
	cmd_node = 0;
	io_node = 0;
	dup_token = dup_node(token);
	cur_root = root;
	while (cur_root->right != NULL)											//pipe 타고 들어가기
		cur_root = cur_root->right;
	cmd_node = tree_search_type(cur_root, 4);						//CMD type_only 찾기
	if (token->type == LEFT_DOUBLE_REDI)						//HEREDOC 우선순위 처리
	{
		if (cmd_node->left->left->left)							//CMD->IO->REDIR->leaf 유/무 확인
		{
			buf = cmd_node->left;								//기존에 있던 IO 서브트리 보존
			left_subtree(cmd_node, type_only_node(3));			//새 IO 생성
			left_subtree(cmd_node->left, type_only_node(2));	//새 REDIR 생성
			left_subtree(cmd_node->left->left, dup_token);		//REDIR 아래로 토큰 삽입
			right_subtree(cmd_node->left, buf);					//새 IO->right 에 기존 IO 연결
		}
		else
			left_subtree(cmd_node->left->left, dup_token);
	}
	else
	{
		io_node = cmd_node->left;
		if (!check_io_leaf(io_node))
			left_subtree(io_node->left, dup_token);
		else
		{
			while (io_node->right)
				io_node = io_node->right;
			right_subtree(io_node, type_only_node(3));
			left_subtree(io_node->right, type_only_node(2));
			left_subtree(io_node->right->left, dup_token);
		}
	}
	return (root);
}

t_tree	*tree_bin(t_tree *root, t_token *token)
{
	t_tree	*bin_node;
	t_tree	*dup_token;
	t_tree	*cur_root;

	bin_node = 0;
	dup_token = dup_node(token);
	cur_root = root;
	while (cur_root->right != NULL)
		cur_root = cur_root->right;
	bin_node = tree_search_type(cur_root, 1);
	left_subtree(bin_node, dup_token);
	return (root);
}
