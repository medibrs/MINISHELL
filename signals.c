/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmestini <bmestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:50:23 by bmestini          #+#    #+#             */
/*   Updated: 2024/10/08 08:50:25 by bmestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interact_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_code(*((get_collector())->env), 130);
}

void	interact_sigquit(int sig)
{
	(void)sig;
	return ;
}

void	act_sigint(int sig)
{
	(void)sig;
	printf("\n");
	f_at_exit();
	exit(130);
}

void	act_sigquit(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}

void	handle_sig(void (*sigint)(int), void (*sigquit)(int),
		void (*sigint_old)(int), void (*sigquit_old)(int))
{
	struct sigaction	s_int;
	struct sigaction	s_int_old;
	struct sigaction	s_quit;
	struct sigaction	s_quit_old;

	s_int.sa_handler = sigint;
	sigemptyset(&s_int.sa_mask);
	s_int.sa_flags = 0;
	s_int_old.sa_handler = sigint_old;
	sigemptyset(&s_int_old.sa_mask);
	s_int_old.sa_flags = 0;
	sigaction(SIGINT, &s_int, &s_int_old);
	s_quit.sa_handler = sigquit;
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_flags = 0;
	s_quit_old.sa_handler = sigquit_old;
	sigemptyset(&s_quit_old.sa_mask);
	s_quit_old.sa_flags = 0;
	sigaction(SIGQUIT, &s_quit, &s_quit_old);
}
