/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:41:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/25 17:39:54 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initiate the parser structure, see in minishell.h.

t_parser	init_struct(t_lexer *lexer, t_mini *mini)
{
	t_parser	parser;

	parser.lexer = lexer;
	parser.redirections = NULL;
	parser.num_redirections = 0;
	parser.mini = mini;
	return (parser);
}

t_simple_cmd	*init_cmd(t_parser *parser)
{
	//char	**str;
	//int		i;

	//redirections;
	redirections(parser);
	return (new_simple_cmd(NULL, parser->num_redirections, parser->redirections));
}

int	parser(t_mini *mini)
{
	int	i = 0;
	t_parser		parser;
	t_simple_cmd	 *cmd;

	count_pipes(mini); //ok
	printf("PIPES = %d\n", mini->pipes);
	while (mini->lexer && i < lst_size(mini)) //TEST i < lst_size TEST
	{
		if (mini->lexer && mini->lexer->token == PIPE)
			del_first_node(&mini->lexer);
		//ft_print(mini);
		parser = init_struct(mini->lexer, mini);
		cmd = init_cmd(&parser);
		//ft_print(mini);
		printf("--------------------------------------------\n");
		//ft_print(mini);
		i++;
		break ;
	}
	return (0);
}
