/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:33:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/21 12:31:21 by simarcha         ###   ########.fr       */
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
/*
void	sigint_handler(void (*)(t_mini *)mini)
{
	if (!mini->inside_hdoc)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (mini->inside_hdoc == 1 && mini->inside_cmd == 1)
	{
		mini->outside_hdoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//(void)signal;
}

void	init_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
*/

t_mini *g_mini = NULL;

void sigint_handler(int signum)
{
    if (!g_mini->inside_hdoc)
        ft_putstr_fd("\n", STDERR_FILENO);
    if (g_mini->inside_hdoc == 1 && g_mini->inside_cmd == 1)
    {
        g_mini->outside_hdoc = 1;
        rl_replace_line("", 0);
        rl_redisplay();
        rl_done = 1;
        return;
    }
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)signum; // Pour éviter l'avertissement de variable inutilisée
}

void	init_signals(t_mini *mini)
{
	g_mini = mini;

    rl_event_hook = event;
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}
/*
typedef struct s_signal_context {
    t_mini *mini;
    void (*handler)(t_mini *);
} t_signal_context;

// Fonction intermédiaire pour gérer le signal
void sigint_handler_wrapper(int signum, void *ucontext) {
    t_signal_context *context = (t_signal_context *)ucontext;
    t_mini *mini = context->mini;
    
    if (!mini->inside_hdoc)
        ft_putstr_fd("\n", STDERR_FILENO);
    if (mini->inside_hdoc == 1 && mini->inside_cmd == 1)
    {
        mini->outside_hdoc = 1;
        rl_replace_line("", 0);
        rl_redisplay();
        rl_done = 1;
        return;
    }
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)signum; // Pour éviter l'avertissement de variable inutilisée
}

// Fonction pour initialiser les signaux
void init_signals(t_mini *mini) {
    static t_signal_context context;
    context.mini = mini;
    context.handler = sigint_handler_wrapper;

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigint_handler_wrapper;
    sigemptyset(&sa.sa_mask);

    // Utilisez sigaction au lieu de signal pour passer le contexte
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}*/