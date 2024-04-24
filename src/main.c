/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/24 13:22:35 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function for free all and call another time mini_live for create a loop

static int	reset(t_mini *mini)
{
	t_lexer	*tmp;

	tmp = mini->lexer;
	while (tmp->next)
	{
		tmp = tmp->next;
		free(tmp);
	}
	mini_live(mini);
	return (0);
}

// this function is for do the cycle of live for every line receives from readline

int	mini_live(t_mini *mini)
{
	mini->line = readline("minihell 🔥 >");
	if (check_quotes(mini->line) != 0)
		return (1); // display error
	if (lexer_tokenizer(mini) != 0)
		return (1); //display_error
	//lexer
	//parser
	//executor
	//free and reset
	reset(mini);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
  t_mini	mini;

	if (argc != 1)
	{
		printf("Don't write any argument");
		exit(0);
	}
	printf("no %s%s\n", argv[0], env[1]);
	mini_live(&mini);
	return (0);
}
