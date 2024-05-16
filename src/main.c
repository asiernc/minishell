/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/16 16:49:56 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// function for free all and call another time mini_live for create a loop

int	reset(t_mini *mini)
{
	if (mini->cmd)
		lst_clear_cmds(&mini->cmd);
	if (mini->lexer)
		lst_clear_lexer(&mini->lexer);
	mini_live(mini);
	return (0);
}

// this function is for do the cycle of live for every line receives from readline

int	mini_live(t_mini *mini)
{
	// valorar hacer un bucle para no forzar a que entre dentor de una funcion de otra de otra de otra
	mini->line = readline("shelldone 🔥 >");
	//check_quotes(mini->line);
	if (lexer_tokenizer(mini) != 0)
		print_error(mini, mini->lexer, 1); //display_error
	parser(mini);
	pre_executor(mini);
	//free and reset
	reset(mini);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	if (argc != 1 && argv[0])
	{
		printf("Don't write any argument");
		exit(0);
	}
	mini.env = env;
	//printf("no %s%s\n", argv[0], env[1]);
	mini_live(&mini);
	return (0);
}
