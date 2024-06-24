/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:33:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/20 10:00:22 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int signal)
{
	(void)signal;
	ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
}

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int signal)
{
	if (!g_global_var.inside_hdoc)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (g_global_var.inside_hdoc == 1 && g_global_var.inside_cmd == 1)
	{
		g_global_var.outside_hdoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
}

void	init_signals(void)
{
	rl_event_hook = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
