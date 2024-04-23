/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/23 16:31:56 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this function is for do the cycle of live for every line receives from readline
int	mini_live(t_mini *mini)
{
	mini->line = readline("minihell 🔥 >");
	printf("%s\n", mini->line);
	//if (!check_quotes(mini->line))
	//	return (1); // display error
	lexer_tokens(mini);
	//if (lexer_tokens(mini) != 0)
	//	return (1); //display_error
	//lexer
	//parser
	//executor
	//free and reset
	return (0);
}

int	main(int argc, char **argv, char **env)
{
  t_mini	mini;

  //char str[] = "ls -l | grep a > file";

	if (argc != 1)
	{
		printf("Don't write any argument");
		exit(0);
	}
	printf("no %s%s\n", argv[0], env[1]);
	mini_live(&mini);
	return (0);
}
