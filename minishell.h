/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:56:53 by kyukim            #+#    #+#             */
/*   Updated: 2022/02/07 12:47:38 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_list
{
	void			*key;
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_arg
{
	void			*arg;
	struct s_arg	*next;
}					t_arg;
typedef struct s_cmd
{
	char			*cmd;
	char			*option;
	struct s_arg	*args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_info
{
	char			**cmd;
	int				pipe_flag;
	int				redirection_flag;
	int				double_shift_flag;
}	t_info;

typedef struct s_mark
{
	int				double_quote;
	int				quote;
	int				space;
	int				l_double_shift;
	int				r_double_shift;
	int				l_shift;
	int				r_shift;
	int				pipe;
	int				option;
}					t_mark;

char	*sh_strchr(const char *s, int c);
t_list	*sh_lstlast(t_list *lst);
void	sh_lstadd_back(t_list **lst, t_list *new);
size_t	sh_strlen(const char *s);
char	*sh_substr(char const *s, unsigned int start, size_t len);
int		sh_strcmp(char *dst, char *src);

//init.c
int	init_info(t_info **info);
int	init_cmd_s(t_cmd **cmd_s);
int	check_info(t_info *info);

//tokenize.c
int	tokenize_fullcmd(t_cmd *cmd, char *full_cmd, char **cmds);

//lst.c
t_list	*sh_lstnew(void *content);
t_arg	*arg_new(void);
t_cmd	*cmd_new(void);

#endif