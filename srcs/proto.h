#ifndef PROTO_H
# define PROTO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# include "../lib/libft.h"

# define	O_ENV 1
# define	T_EXPORT 2

# define	CHARACTERS 0
# define	FTSPACE 1
# define	PIPE 2
# define	LEFT_REDI 3
# define	RIGHT_REDI 4
# define	LEFT_DOUBLE_REDI 5
# define	RIGHT_DOUBLE_REDI 6
# define	PATH 7
# define 	SINGLE 8
# define 	DOUBLE 9
# define	BUILTIN 10
# define	OPTION 11
# define	CMD 12
# define	PSPIPE 13
# define	PSCMD 14
# define	PSIO 15
# define	PSREDIR 16
# define	PSBIN 17
# define	SIGINT_WITH_FORK 1300
# define	SIGQUIT_WITH_FORK 1310


# define	STANDARD 100

typedef struct s_flag
{
	int num;
	int len[STANDARD];
	int i_cur[STANDARD];
	int type[STANDARD];
}				t_flag;

typedef	struct s_new_line
{
	int start;
	int left_space;
	int right_space;
	int new_len;
	int num;
}				t_new_line;

typedef	struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_tree
{
	int				type;
	char			**data;
	int				pip[2];
	int				prepip;
	int				my_number;
	int				my_my;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct s_list
{
	int				type;
	void			*key;
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_debug
{
	char			*syntax_error;
	void			*error_point_data;
}					t_debug;

typedef struct s_heredoc
{
	int				use_number;
	int				pip[2];
}				t_heredoc;

typedef struct s_info
{
	char			**env;
	char			**origin_env;
	int				my_num;
	t_heredoc		*heredoc;
	t_list			*e_head;
	t_token			*t_head;
	t_tree			*root;
	t_debug			*debug;
}					t_info;

int exit_signal;

typedef void (*VisitFuncPtr)(t_info *info, t_tree *tree);

//init.c
int		init_info(t_info **info);

//signal.c
void	set_signal();
void	signal_handler(int signum);

//copy.c
int		copy_env(t_info *info, char *env[]);

//util.c
size_t	sh_strlen(const char *s);
char	*sh_substr(char const *s, unsigned int start, size_t len);
char	*sh_strchr(const char *s, int c);
void	check_data(char *message, char **data);

//add_str.c
char	**add_str(char **str, char **new);

//lst.c
t_token	*kb_lstnew(void);
t_token	*kb_lstlast(t_token *lst);
void	lstadd_front(t_token **lst, t_token *new);

//sh_lst.c
t_list	*sh_lstnew(void *content);
t_list	*sh_lstlast(t_list *lst);
void	sh_lstadd_back(t_list **lst, t_list *new);
void	*find_content_from_key(t_list *env, char *key);
void	add_head(t_info *info, int type);

//tokenize.c
void	tokenize(char *full_command, t_info *info);
int 	characters_len(char *cmd, int i);
int		check_status_type(char c);

//free.c
void	free_before_newline(t_info *info);

//free_token.c
// void	free_token(t_token *head);
t_token	*find_heredoc(t_token *token);

//cmd_env.c
char 	*change_cmd_to_env(char *cmd, t_flag flag, t_info *info);

//tokenize_utill.c
void	make_token_node(char *cmd, t_flag flag, t_info *info);
int		token_len_check(char *s, int i, t_flag *flag);

//print_node.c
void	print_t_token(t_info *info);
void	print_env(t_info *info);
void	print_tree(t_tree *root, int level);

//syntax_hub.c
int		syntax_hub(t_token *head, t_debug *debug);

//check_order.c
int		syntax_redir(t_token *tokens, t_debug *debug);
int		check_order(t_token *tokens, t_debug *debug);

//set_type.c
int		set_type(t_token *head);
int		syntax_word(t_token *tokens,t_debug *debug);

//tree_util.c
t_tree	*dup_node(t_token *token, int child_number, int child_child);
t_tree	*type_only_node(int type);
void	left_subtree(t_tree *root, t_tree *sub);
void	right_subtree(t_tree *root, t_tree *sub);
t_tree	*tree_search_type(t_tree *root, int type);

//parse.c
int		parse_tree(t_info *info);

//tree_io.c
t_tree	*tree_io(t_tree *root, t_tree *new);

//tree_pipe.c
t_tree	*tree_pipe(t_tree *root, t_tree *new);

//tree_bin.c
t_tree	*tree_bin(t_tree *root, t_tree *new);

//tree_arg.c
t_tree	*tree_arg(t_tree *root, t_tree *new);

//del_tree.c
void	postorder_del_tree(t_tree *root);
void	del_node(t_tree *node);

//builtin.c
void	implement_cmd(t_info *info, char **cmd);
int		str_len(char **str);
void	env_add(t_info *info, char *key, char *content);
int		check_builtin(t_tree *tree);

//builtin_env.c
void	builtin_env(t_info *info, char **str);

//builtin_export.c
void	builtin_export(t_info *info, char **str);

//builtin_unset.c
void	builtin_unset(t_info *info, char **str);

//builtin_pwd.c
void	builtin_pwd(char **str);

//builtin_cd.c
void	builtin_cd(t_info *info, char **str);

//builtin_echo.c
void	builtin_echo(char **str);

//builtin_exit.c
void	builtin_exit(t_info *info, char **str);

//redir.c
void	redir_hub(t_info *info, t_tree *root);

//heredoc.c
int		heredoc(t_info *info);

//execve.c
void		run_execve(char **cmd_data, char *env, char **origin_env);

//action/action_tree.c
void	action(t_info *info, int in, int out);

//action/preorder.c
void	single_tree(t_info *info, t_tree *tree, int in, int out);
void	preorder_traverse(t_info *info, t_tree *tree);

void	execv_cmd(t_info *info, char **str);
#endif
