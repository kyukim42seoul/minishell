/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:38:10 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/25 19:36:44 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define O_ENV 1
# define T_EXPORT 2

# define CHARACTERS 0
# define FTSPACE 1
# define PIPE 2
# define LEFT_REDI 3
# define RIGHT_REDI 4
# define LEFT_DOUBLE_REDI 5
# define RIGHT_DOUBLE_REDI 6
# define PATH 7
# define SINGLE 8
# define DOUBLE 9
# define BUILTIN 10
# define OPTION 11
# define CMD 12
# define PSPIPE 13
# define PSCMD 14
# define PSIO 15
# define PSREDIR 16
# define PSBIN 17
# define SIGINT_WITH_FORK 1300
# define SIGQUIT_WITH_FORK 1310
# define STANDARD 100

int	g_exit_signal;

typedef struct s_flag
{
	int	num;
	int	len[STANDARD];
	int	i_cur[STANDARD];
	int	type[STANDARD];
}				t_flag;

typedef struct s_new_line
{
	int	start;
	int	left_space;
	int	right_space;
	int	new_len;
	int	num;
}				t_new_line;

typedef struct s_token
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
	char			**env_array;
	int				my_num;
	t_heredoc		*heredoc;
	t_list			*e_head;
	t_token			*t_head;
	t_tree			*root;
	t_debug			*debug;
}					t_info;

#endif
