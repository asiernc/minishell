/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:49:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/20 17:24:15 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//we want a function to know if the expanded variable has to be expanded or not
//for example, if we have: echo '$test' => we don't have to expand it =>output: $test
//but if we have		 : echo "$test" => we have to expand it => output : content of test
//basically if the content is between simple quotes => we don't expand it
//else (there is no quotes or double quotes), we expand it

//we want to return a int to know if we have to expand it or not
//it means if we are in a double or a single quote
int	expand_or_not(char *str)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			if (check == 1)
				check = 0;
			else
				check = 1;
		}
		i++;
	}
	return (!check);
}

int	expand_or_not(char *str)
{
	int	i;
	int	sq_check;
	int	dq_check;

	i = 0;
	sq_check = 0;
	dq_check = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE && sq_check == 0)
			dq_check = !dq_check;
		if (str[i] == QUOTE && dq_check == 0)
			sq_check = !sq_check;
		i++;
	}
	if (dq_check == 0)
		return (1);
	return (0);
}

char	*expand_or_not(char *str)
{
	int		simple_quote;
	int		double_quote;
	char	*result;
	int		i;

	i = 0;
	simple_quote = 0;
	double_quote = 0;
	if check_all_quotes_closed(str) == 0)
		print_error//not well written
	while (str[i])
	{
		if (str[i] == DQUOTE && simple_quote == 0)
			double_quote = !double_quote;
		else if (str[i] == QUOTE && double_quote == 0)
			simple_quote = !simple_quote;
		else if (simple_quote == 1)
			result[i] += str[i];
		else if (double_quote == 1)
		{
			//if it's a $
			//else if it's a \\ 
			else
				result[i] += str[i];
		i++;
	}
	return (result);
}

//we have to check if all quotes are closed to execute command with quotes
//if there is one open, we return 0. It means the command can't be executed
int	check_all_quotes_closed(char *str)
{
	int	simple_quote;
	int	double_quote;
	int	i;

	simple_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
			simple_quote = !simple_quote;
		if (str[i] == DQUOTE)
			double_quote = !double_quote;
		i++;
	}
	if (simple_quote == 0 && double_quote == 0)
		return (1);
	return (0);
}
