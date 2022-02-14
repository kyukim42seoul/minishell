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

#define	O_ENV 1;
#define T_EXPORT 2;

//	함수 공간

// typedef struct s_rb
// {
// 	t_node			*root;
// 	t_rb_cmp_fn		compare;
// }					t_rb;

typedef struct s_list
{
	int				type;
	void			*key;
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_info
{
	char			**cmd;
	int				pipe_flag;
	int				redirection_flag;
	int				double_shift_flag;
	t_list			*head;
}					t_info;


//init.c
int	init_info(t_info **info);

//copy.c
int	copy_env(t_info *info, char *env[]);

//util.c
size_t	sh_strlen(const char *s);
char	*sh_substr(char const *s, unsigned int start, size_t len);
char	*sh_strchr(const char *s, int c);

//lst.c
t_list	*sh_lstnew(void *content);
t_list	*sh_lstlast(t_list *lst);
void	sh_lstadd_back(t_list **lst, t_list *new);



#endif
