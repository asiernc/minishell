/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:22:39 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/23 14:17:16 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_line(t_mini *mini)
{
	char	*tmp;

	tmp = ft_strtrim(mini->line);
	free(mini->line);
	mini->line = tmp;
}

int	check_token(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

int	find_token(int c)
{
	static int operator = {
		{'|', PIPE},
		{'<', RED_IN},
		{'>', RED_OUT},
	}
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
	if (operator == RED_IN && find_token(str[i + 1]) == RED_IN)
	{
		if (list_add_node(&lst, operator, NULL) == 1)
			return (1); //put error because 1 is not a sum
		return (2);
	}
	else if (operator == RED_OUT && find_token(str[i + 1]) == RED_OUT)
	{
		if (list_add_node(&lst, operator, NULL) == 1)
			return (1);
		return (2);
	}
	else if (operator)
	{
		if (list_add_node(&lst, operator, NULL) == 1)
			return (1);
		return (1);
	}
	return (0);
}

int	put_word(char *str, int i, t_lexer **lst)
{
	int	j;

	j = 0;
	while (str[i] && find_token(str[i]) != 0)
	{
		if (str[i] == 34)
			j += find_next_quote();
		if (str[i] == 39)
			j += find_next_quote();
		j++;
		i += j;
	}

int	lexer_tokens(t_mini *mini)
{
	int	i;
	int	dif;

	clear_line(mini);
	i = 0;
	dif = 0;
	while (mini->line[i])
	{
		diff = 0;
		if (check_token(mini->line[i]))
			diff = put_token(mini->line, i, &mini->lexer);
		else // a word witt or no quotes
			diff = put_word();

		i += diff;
		i++;
	}
}

