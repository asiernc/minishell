/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:58:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/23 17:21:05 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//you have to check that in the line read, all the quotes are closed
//and the end of the line is not a PIPE
//=>Otherwise we gave error

int	print_error(char *str)
{
	perror(str);
	exit(1);
}

/*void	check_quotes(char *line)
{
	int	simple_quotes_counter;
	int	double_quotes_counter;
	int	i;

	i = 0;
	simple_quotes_counter = 0;
	double_quotes_counter = 0;
	while (line[i])
	{
		if (line[i] == 39)//39 refers to ' in the ascii table
			simple_quotes_counter++;
		else if (line[i] == 34)//34 refers to " in the ascii table
			double_quotes_counter++;
		if (simple_quotes_counter > 0 && simple_quotes_counter % 2 == 0) 
		{
//			simple_quotes_counter = 0;
			double_quotes_counter = 0;
		}
		else if (double_quotes_counter > 0 && double_quotes_counter % 2 == 0)
		{
			simple_quotes_counter = 0;
//			double_quotes_counter = 0;
		}

		i++;
	}
	i--;
//	printf("simple quote counter = %i\n double quote counter = %i\n", simple_quotes_counter, double_quotes_counter);
	if (simple_quotes_counter % 2 == 1 || double_quotes_counter % 2 == 1 ||
		line[i] == '|' || line[i] == '>' || line[i] == '<')
		print_error("The line was not well written. Please try again.");
//	printf("everything's good");
}*/

/*int	count_simple_quotes(char *line, int *i, int *counter)
{
	if (*i != ((int)ft_strlen(line) - 1) && line[*i] == 39)//39 <=> ' 
	{
		(*counter)++;
		(*i)++;
		while (line[*i] && line[*i] != 39)
			(*i)++;
		if (line[*i] == 39)
		{
			(*counter)++;
			(*i)++;
		}
	}
}*/

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
