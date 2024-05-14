/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:41:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/14 16:51:32 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// printf final test struct

void	ft_print_parser(t_mini *mini)
{
	t_cmd	*tmp;
	//t_lexer			*tmp2;
	int	i = 0;
	int	len = lst_size_cmd(mini);

	printf("1111111111STRING : %s\n", mini->cmd->next->str[0]);
	tmp = mini->cmd;
	printf("LEN %d\n", len);
	//tmp2 = mini->simple_cmd->redirections;
	while (tmp)
	{
		printf("1\n");
		printf("Node %d, str** = %s;",
			   	i, tmp->str[0]);
		/*printf("Node %d, str** = %s;",
			   	i, tmp->str[1]);*/

		//if (tmp2->str)
		//	printf("redirections str = %s, operator = %d", tmp2->str,
		//		tmp2->token);
		tmp = tmp->next;
		//tmp2 = tmp2->next;
		printf("\n");
		i++;
	}
}

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

t_cmd	*create_cmd(t_parser *parser)
{
	char	**str;
	int		i;
	int		num_args;
	t_lexer	*tmp;

	redirections(parser);
	num_args = count_args(parser->lexer);
	str = malloc((num_args + 1) * sizeof(char *));
	if (!str)
		print_error(parser->mini, parser->mini->lexer, 1);
	i = 0;
	tmp = parser->lexer;
	while (i < num_args)
	{
		if (tmp->str)
		{
			str[i] = ft_strdup(tmp->str);
			//printf("NEW CMD: %s\n", str[i]);
			delone_node(tmp->num_node, &parser->lexer);
			//del_first_node(&parser->lexer);
			tmp = parser->lexer;
		}
		i++;
	}
	return (new_cmd(str, parser->num_redirections, parser->redirections));
}

int	parser(t_mini *mini)
{
	t_parser		parser;
	t_cmd			 *new;

	count_pipes(mini);
	//printf("PIPES = %d\n", mini->pipes);
	while (mini->lexer)
	{
		if (mini->lexer && mini->lexer->token == PIPE)
			del_first_node(&mini->lexer);
		if (check_line(mini, mini->lexer->token))
			return (EXIT_FAILURE);
		parser = init_struct(mini->lexer, mini);
		new = create_cmd(&parser);
		//printf("string %s\n", cmd->str[0]);
		if (!new)
			print_error(mini, mini->lexer, 0);
		if (!mini->cmd)
			mini->cmd = new;
		else
			ft_node_add_back_parser(&mini->cmd, new);
		mini->lexer = parser.lexer;
	}
//	printf("node 1 ls == %s\nnode 2 wc == %s\n", mini->cmd->str[0], mini->cmd->next->str[0]);
	// !! siguientes dos lineas son para mac m2 !!!
	//mini->cmd = mini->cmd->next;
	//mini->cmd->previous = NULL;
	int size = lst_size_cmd(mini);
	printf("SIZE %d\n", size);
	//del_first_cmd(&mini->cmd);
	//ft_print_parser(mini);
	//print_error(mini, mini->lexer, 0);
	return (EXIT_SUCCESS);
}

