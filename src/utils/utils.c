/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:07:20 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/24 12:43:30 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_next(char *line, int *counter, int i, int lim)
{
	int	index;

	index = 0;
	*counter += 1;
	if (line[i] == lim)
	{
		index++;
		while (line[index] && line[index] != lim)
			index++;
	}
	//index++;
	if (line[index] == lim)
		*counter += 1;
	//index++;
	return (index);
}

int	check_quotes(char *line)
{
	int	simple_quotes;
	int	double_quotes;
	int	i;

	i = 0;
	simple_quotes= 0;
	double_quotes= 0;
	while (line[i])
	{
		if (line[i] == 39)//39 refers to ' in the ascii table
			i += find_next(line, &simple_quotes, i, 39);
		if (line[i] == 34)//34 refers to " in the ascii table
			i += find_next(line, &double_quotes, i, 34);
		i++;
	}
	if (simple_quotes % 2 == 0 || double_quotes % 2 == 0)// ||
	//	line[i] == '|' || line[i] == '>' || line[i] == '<')
	{
		printf("everything's good\n");
		return (0);
	}
	printf("The line was not well written. Please try again.\n");
	return (1);
	// Here's a function that looks for a pipe character and then continues searching to find any letter character
}
