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


typedef struct s_list
{
	int				type;
	void			*key;
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_info
{
	char			*cmd;
	int				pipe_flag;
	int				redirection_flag;
	int				double_shift_flag;
	t_list			*head;
	t_token			*t_head;
}					t_info;



//init.c
int		init_info(t_info **info);

//copy.c
int		copy_env(t_info *info, char *env[]);

//util.c
size_t	sh_strlen(const char *s);
char	*sh_substr(char const *s, unsigned int start, size_t len);
char	*sh_strchr(const char *s, int c);

//lst.c
t_list	*sh_lstnew(void *content);
t_list	*sh_lstlast(t_list *lst);
void	sh_lstadd_back(t_list **lst, t_list *new);
t_token	*kb_lstlast(t_token *lst);
t_token	*kb_lstnew(void);

//tokenize.c
void	input_tokenize(char *full_command, t_info *info);
int 	characters_len(char *cmd, int i);

//cmd_env.c
char 	*change_cmd_to_env(char *cmd, t_flag flag, t_info *info);

//tokenize_utill.c
void	make_token_node(char *cmd, t_flag flag, t_info *info);
int		token_len_check(char *s, int i, t_flag *flag);

//print_node.c
void	print_t_token(t_info *info);

#endif
