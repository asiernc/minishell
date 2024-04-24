/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:22:39 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/23 23:38:13 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 

void	clear_line(t_mini *mini)
{
	char	*tmp;

	tmp = ft_strtrim(mini->line, " ");
	free(mini->line);
	mini->line = tmp;
	printf("%s\n", mini->line);
}

// This function serves to check if that character is an operator. 
// If so, we assign a value to that key (operator character).

int	check_operator(int c)
{
	int	i;
	int operator[3][2] = {
		{'|', PIPE},
		{'<', RED_IN},
		{'>', RED_OUT},
	};

	i = -1;
	while (++i <= 2)
		if (operator[i][0] == c)
			return (operator[i][1]);
	return (0);
}

// This function assigns a value to that operator as desired. The only 
// different ones are '>>' and '<<', so we create a special case for 
// each of them. If not, we assume it's '|', '<', or '>'.

int	put_token(char *str, int i, t_lexer **lst)
{
	t_operator	operator;

	operator = check_operator(str[i]);
	if (operator == RED_IN && check_operator(str[i + 1]) == RED_IN)
	{
		operator = HDOC;
		if (list_add_node(lst, operator, NULL) == 1)
			return (-2); //create put error because 1 is not a sum
		return (2);
	}
	else if (operator == RED_OUT && check_operator(str[i + 1]) == RED_OUT)
	{
		operator = RED_OUT_APP;
		if (list_add_node(lst, operator, NULL) == 1)
			return (-2);
		return (2);
	}
	else if (operator)
	{
		if (list_add_node(lst, operator, NULL) == 1)
			return (-2);
		return (1);
	}
	//printf("OPERATOR %d\n", operator);
	return (0);
}

// Traverse the string from that quote until the next character that
// matches the first one.

int	find_next_quote(char c, char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != c)
	   j++;
	j++;
	//printf("valor j: %d\n", j);
	return (j);
}	

// Identify the word, trim it from spaces, and add it as a new node.
// Also, identify quotes.

int	put_word(char *str, int i, t_lexer **lst)
{
	int	j;

	j = 0;
	//printf("STRRRRR: %s\n", str);
	while (str[i + j] && check_operator(str[i + j]) == 0)
	{
		if (str[i + j] == 34 || str[i + j] == 39)
			j += find_next_quote(str[i + j], str, i + j) - 1;
		else if (str[i + j] != ' ' && str[i + j] != '\t')
			j++;
		else
			break ;
	}
	//printf("VALOR J: %d\n", j);
	printf("SUBSTRING - %s\n", ft_substr(str, i, j));
	if (list_add_node(lst, 0, ft_substr(str, i, j)))
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
		i++;
		printf("Node %d, str = %s  token(ope) = %d\n", i, tmp->str, tmp->token);
		tmp = tmp->next;
	}
}

// This function separate the command line, distinguish between operator and word.

int	lexer_tokens(t_mini *mini)
{
	int	i;
	int	diff;

	clear_line(mini);
	i = 0;
	while (mini->line[i])
	{
		//printf("VALOR DE i ==> %d\n", i);
		diff = 0;
		while (mini->line[i] == ' ' || (mini->line[i] > 8 && mini->line[i] < 14))
			i++;
		if (check_operator(mini->line[i]) != 0)
			diff = put_token(mini->line, i, &mini->lexer);
		else
			diff = put_word(mini->line, i, &mini->lexer);
		if (diff < 0)
			return (0);
		//printf("VALOR DE i antes de sumar diff: %d, diff%d\n", i, diff);
		i += diff;
		//printf("VALOR DE i después de sumar diff: %d\n", i);
	}
//	printf("str1: %s\n", mini->lexer->str);
	ft_print(mini);
	return (0);
}
