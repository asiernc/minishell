/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:22:39 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/23 17:11:45 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_line(t_mini *mini)
{
	char	*tmp;

	tmp = ft_strtrim(mini->line, " ");
	free(mini->line);
	mini->line = tmp;
	printf("%s\n", mini->line);
}

int	check_token(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	find_token(int c)
{
	static int operator[3][2] = {
		{'|', PIPE},
		{'<', RED_IN},
		{'>', RED_OUT}
	};
	int			i;

	i = -1;
	while (++i <= 2)
		if (operator[i][0] == c)
			return (operator[i][1]);
	return (0);
}

int	put_token(char *str, int i, t_lexer **lst)
{
	t_operator	operator;

	operator = find_token(str[i]);
	printf("operator: %d\n", operator);
	if (operator == RED_IN && find_token(str[i + 1]) == RED_IN)
	{
		if (list_add_node(lst, operator, NULL) == 1)
			return (1); //put error because 1 is not a sum
		return (2);
	}
	else if (operator == RED_OUT && find_token(str[i + 1]) == RED_OUT)
	{
		if (list_add_node(lst, operator, NULL) == 1)
			return (1);
		return (2);
	}
	else if (operator)
	{
		if (list_add_node(lst, operator, NULL) == 1)
			return (1);
		return (1);
	}
	return (0);
}

int	find_next_quote(char c, char *str, int i)
{
	int	k;

	k = 0;
	if (str[i + k] == c)
	{
		k++;
		while (str[i + k] && str[i + k] != c)
		   k++;
		k++;
	}
	return (k);
}	

int	put_word(char *str, int i, t_lexer **lst)
{
	int	j;

	j = 0;
	while (str[i] && find_token(str[i]) != 0)
	{
	//	if (str[i] == 34)// "
			j += find_next_quote(34, str, i + j);
	//	if (str[i] == 39)// '
			j += find_next_quote(39, str, i + j);
		if (str[i + j] == ' ' || str[i + j] == '\t')
			break ;
		else
			j++;
	}
	printf("1- %s\n", ft_substr(str, i, j));
	if (!list_add_node(lst, 0, ft_substr(str, i, j)))
		return (1);
	return (j);
}

static void	ft_print(t_mini *mini)
{
	t_lexer	*tmp;
	int	i = 0;

	tmp = mini->lexer;
	while (tmp)
	{
		write(1, "in\n", 3);
		i++;
		printf("Node %d, str = %s, token(ope) = %d\n", i, tmp->str, tmp->token);
		tmp = tmp->next;
	}
}

int	lexer_tokens(t_mini *mini)
{
	int	i;
	int	diff;
	//t_lexer	*test;

//	write(1, "inside\n", 8);
//	test = ft_new_node("hola", 0);
//	printf("node %s", test->str);
	clear_line(mini);
	i = 0;
	diff = 0;
	while (mini->line[i])
	{
		printf("CHAR %c\n", mini->line[i]);
		diff = 0;
		//if (check_token(mini->line[i]) == 0)
		if (find_token(mini->line[i]))
			diff = put_token(mini->line, i, &mini->lexer);
		else // a word witt or no quotes
			diff = put_word(mini->line, i, &mini->lexer);
		if (diff < 0)
			return (0);
		i += diff;
	}
//	printf("str1: %s\n", mini->lexer->str);
	ft_print(mini);
	return (0);
}

