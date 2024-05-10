/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:01:02 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/10 11:45:02 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int builtin_test(t_mini *mini, t_simple_cmd *simple_cmd);

/*builtin	find_builtin(char *str)
{
	int					i;
	static void *func[7][2] = 
	{
    	{"echo", builtin_test},
		{"cd", builtin_test},
		{"pwd", builtin_test},
		{"export", builtin_test},
		{"unset", builtin_test},
		{"env", builtin_test},
		{"exit", builtin_test}	
	};

	i = 0;
	if (!str)
		return (NULL);
	while (i < 7)
	{
		if (ft_strcmp(str, func[i][0]) == 0)
			return (func[i][1]);
		i++;
	}
	return (NULL);
}*/

e_builtin	prepare_builtin(char *str)
{
	if (ft_strcmp(str, "echo" == 0))
		return (ECHO);
	else if (ft_strcmp(str, "cd" == 0))
		return (CD);
	else if (ft_strcmp(str, "pwd" == 0))
		return (PWD);
	else if (ft_strcmp(str, "export" == 0))
		return (EXPORT);
	else if (ft_strcmp(str, "unset" == 0))
		return (UNSET);
	else if (ft_strcmp(str, "env" == 0))
		return (ENV);
	else if (ft_strcmp(str, "exit" == 0))
		return (EXIT);
	else
		return (NOT_HAVE);
}


// Function responsible for counting pipes, for further processing.

void	count_pipes(t_mini *mini)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (mini->line[++i])
		if (mini->line[i] == '|')
			count++;
	mini->pipes = count;
}

int	count_args(t_lexer *lst)
{
	int		count;
	t_lexer	*tmp;

	count = 0;
	tmp = lst;
	while (tmp && tmp->token != PIPE)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

t_lexer	*move_to_next_cmd(t_lexer *lst)
{
	while (lst && lst->token != PIPE)
		lst = lst->next;
	return (lst);
}

int	check_line(t_mini *mini, int token)
{
	if (token == PIPE)
	{
		parser_token_error(mini, token);
		return (EXIT_FAILURE);
	}
	else if (!mini->lexer)
	{
		print_error(mini, mini->lexer, 0);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
