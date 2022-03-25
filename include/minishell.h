#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "struct.h"

typedef void (*visitFuncPtr)(t_info *info, t_tree *tree);

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
int	type_count(t_token *head, int type);

//execve.c
void		run_execve(char **cmd_data, char *env, char **origin_env);

//action/action_tree.c
void	action(t_info *info, int in, int out);

//action/preorder.c
void	single_tree(t_info *info, t_tree *tree, int in, int out);
void	preorder_traverse(t_info *info, t_tree *tree);

void	execv_cmd(t_info *info, char **str);

#endif
