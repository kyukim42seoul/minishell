/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 15:56:53 by kyukim            #+#    #+#             */
/*   Updated: 2022/02/04 19:08:50 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*sh_strchr(const char *s, int c);
t_list	*sh_lstnew(void *content);
t_list	*sh_lstlast(t_list *lst);
void	sh_lstadd_back(t_list **lst, t_list *new);
size_t	sh_strlen(const char *s);
char	*sh_substr(char const *s, unsigned int start, size_t len);
int	sh_strcmp(char *dst, char *src);