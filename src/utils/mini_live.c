/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asiercara <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:52:42 by asiercara         #+#    #+#             */
/*   Updated: 2024/05/18 18:11:12 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// this function is for do the cycle of live for every line receives from readline

int	mini_live(t_mini *mini)
{
	// valorar hacer un bucle para no forzar a que entre dentor de una funcion de otra de otra de otra
	//init_mini(mini);
	mini->line = readline("shelldone 🔥 >");
	clear_line(mini);
	if (mini->line[0] == '\0')
		mini_reset(mini);
	add_history(mini->line);
	//check_quotes(mini->line);
	if (lexer_tokenizer(mini) != 0)
		print_error(mini, 1); //display_error
	parser(mini);
	pre_executor(mini);
	//free and reset
	mini_reset(mini);
	return (0);
}

void	init_mini(t_mini *mini)
{
	mini->line = NULL;
	//mini->env = builtin_env??
	mini->lexer = NULL;
	mini->cmd = NULL;
	mini->flag_hdoc = 0;
	mini->pid = NULL;
}


// function for free all and call another time mini_live for create a loop

int	mini_reset(t_mini *mini)
{
	if (mini->cmd)
		lst_clear_cmds(&mini->cmd);
	if (mini->lexer)
		lst_clear_lexer(&mini->lexer);
	//init_mini(mini);
	mini_live(mini);
	return (0);
}


