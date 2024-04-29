/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:41:38 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/29 00:03:05 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// printf final test struct

void	ft_print_parser(t_mini *mini)
{
	t_simple_cmd	*tmp;
	//t_lexer			*tmp2;
	int	i = 0;
	int	len = lst_size_simple_cmd(mini);

	tmp = mini->simple_cmd;
	printf("LEN %d\n", len);
	//tmp2 = mini->simple_cmd->redirections;
	while (i <= len)
	{
<<<<<<< HEAD
		printf("Node %d, str** = %s %s;",
			i, tmp->str[0], tmp->str[1]);
		if (tmp2->str)
			printf("redirections str = %s, operator = %d", tmp2->str,
				tmp2->token);
=======
		printf("Node %d, str** = %s;",
			   	i, tmp->str[0]);
		//if (tmp2->str)
		//	printf("redirections str = %s, operator = %d", tmp2->str,
		//		tmp2->token);
>>>>>>> 676ee8003003d013b9a386ef08589439ac8d4174
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

t_simple_cmd	*create_cmd(t_parser *parser)
{
	char	**str;
	int		i;
	int		num_args;
	t_lexer	*tmp;

	redirections(parser);
	num_args = count_args(parser->lexer);
	str = ft_calloc(num_args, sizeof(char *));
	if (!str)
		return (NULL) ; // error allocation memory
	i = 0;
	tmp = parser->lexer;
	while (i < num_args)
	{
		if (tmp->str)
		{
			str[i] = ft_strdup(tmp->str);
			delone_node(tmp->num_node, &parser->lexer);
			//del_first_node(&parser->lexer);
			tmp = parser->lexer;
		}
		i++;
	}
	return (new_simple_cmd(str, parser->num_redirections, parser->redirections));
}

int	parser(t_mini *mini)
{
	//int	i = 0;
	t_parser		parser;
	t_simple_cmd	 *cmd;

	count_pipes(mini); //ok
	printf("PIPES = %d\n", mini->pipes);
	while (mini->lexer)//&& i < lst_size(mini)) //TEST i < lst_size TEST
	{
		if (mini->lexer && mini->lexer->token == PIPE)
			del_first_node(&mini->lexer);
		// val error si hay || o no hay cmd para no init struct rtrn obreak
		parser = init_struct(mini->lexer, mini);
		cmd = create_cmd(&parser);
		//ft_print(mini);
		//printf("--------------------------------------------\n");
		//mini->simple_cmd = cmd
		//ft_print(mini);
		if (!cmd)
			return (1); //error creating cmd node	
		ft_node_add_back_parser(&mini->simple_cmd, cmd);
		mini->lexer = parser.lexer;
	}
	ft_print_parser(mini);
	return (0);
}

