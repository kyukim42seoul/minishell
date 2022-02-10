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

//	함수 공간

// typedef struct s_rb
// {
// 	t_node			*root;
// 	t_rb_cmp_fn		compare;
// }					t_rb;




typedef struct	s_env
{
	int				type;
	char			*key;
	char			*value;
	struct t_env	*next;
}				t_env;

typedef struct	s_prompt
{
	char		*buff;
}				t_prompt;

/*
** Variable that may be needed at any moment
*/
typedef struct	s_var
{
	bool		exit;
	bool		is_a_tty;
	uint8_t		return_value;
}				t_var;

typedef struct	s_csh
{
	// t_prompt	prompt;
	// t_var		var;
	char		*env_head;
	t_env		*env;
}				t_csh;

#endif
