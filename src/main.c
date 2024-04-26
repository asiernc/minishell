/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/26 12:29:15 by simarcha         ###   ########.fr       */
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
	check_quotes(mini->line);
	printf("ft_strlen(line) = %i\n", (int)ft_strlen(mini->line));
//	check_backslash(mini->line);
	if (lexer_tokens(mini) != 0)
		return (1); //display_error
	//lexer
	//parser
	//executor
	//free and reset
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	**test_env;
	char	*test_pwd;
	int		i = 0;

	if (argc != 1)
	{
		printf("Don't write any argument");
		exit(0);
	}
	printf("no %s%s\n", argv[0], env[1]);
	mini_live(&mini);
	if (ft_strncmp(mini.line, "cd", 2) == 0)
	{	
		write(1, "ENTERED\n", 8);
		test_env = builtin_env(env);
		while (test_env[i])
		{
			printf("%s\n", test_env[i]);
			i++;
		}
		test_pwd = builtin_pwd(env);
		printf("\npwd = %s\n", test_pwd);
		if (chdir("/") == -1)
			perror("chdir function failed");
		i = 0;
		test_env = builtin_env(env);
		while (test_env[i])
		{
			printf("%s\n", test_env[i]);
			i++;
		}
		test_pwd = builtin_pwd(env);
		printf("\npwd = %s\n", test_pwd);
	}
	reset(&mini);
	return (0);
}
