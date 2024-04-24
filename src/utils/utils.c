/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:07:20 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/24 13:38:17 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	find_next(char *line, int *counter, int i, int lim)
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
*/

int	print_error(char *str)
{
	perror(str);
	exit(1);
}

void	check_quotes(char *line)
{
	int	i;
	int	simple_quotes_counter;
	int	double_quotes_counter;

	i = 0;
	simple_quotes_counter = 0;
	double_quotes_counter = 0;
	if (ft_strlen(line) == 1 && (line[i] == 34 || line[i] == 39))
		print_error("The line was not well written. Please try again.");
	while (line[i])
	{
//		count_simple_quotes(line, &i, &simple_quotes_counter);
		if (i != ((int)ft_strlen(line) - 1) && line[i] == 39)//39 <=> '
		{
			simple_quotes_counter++;
			i++;
			while (line[i] && line[i] != 39)
				i++;
			if (line[i] == 39)
			{
				simple_quotes_counter++;
				i++;
			}
//			continue ;
		}
		else if (i != ((int)ft_strlen(line) - 1) && line[i] == 34)//34 <=> "
		{
			double_quotes_counter++;
			i++;
			while (line[i] && line[i] != 34)
				i++;
			if (line[i] == 34)
			{
				double_quotes_counter++;
				i++;
			}
//			continue ;
		}
	}
	if (simple_quotes_counter % 2 == 1 || double_quotes_counter % 2 == 1 ||
		line[i] == '|' || line[i] == '>' || line[i] == '<')
		print_error("The line was not well written. Please try again.");
}
