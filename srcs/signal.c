/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaek <kbaek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:25:32 by kbaek             #+#    #+#             */
/*   Updated: 2022/03/25 18:12:15 by kbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler_quit(int pid)
{
	if (pid == 0)
	{
		exit_signal = SIGQUIT_WITH_FORK;
		write(1, "^\\", 2);
		write(1, "Quit: 3\n", 9);
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
	}	
}

void	signal_handler(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			exit_signal = 1;
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else
		{
			exit_signal = SIGINT_WITH_FORK;
			write(1, "^C", 2);
			write(1, "\n", 1);
		}
	}
	else if (signum == SIGQUIT)
		signal_handler_quit(pid);
	return ;
}

/*
	tcsetattr의 옵션으로 들어가는 optional_actions에 
	TCSNOW는 환경 변수 0으로 등록되어 있는데, 속성을 바로 변경한다는 것을 의미한다.
	SIGINT	= ctrl + c
	SIGQUIT = ctrl + \
*/
void	set_signal(void)
{
	struct termios	term;

	exit_signal = 0;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
