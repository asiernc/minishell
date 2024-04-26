/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:58:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/26 14:24:41 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"
#include <stdio.h>

// NEW NEW NEW NEW

void	print_error(char *str)
{
	perror(str);
//	exit(1);//you don't have to exit => tu have to display a newline
}

void	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34)//"
		{
			i++;
			while (line[i] && line[i] != 34)
			{
//				write(1, "out\n", 4);
				if (line[i] == 92 && i < (int)ft_strlen(line) - 1)
					i++;
				i++;//in this condition, we can also add a string to catch what's inside the quotes
			}
			if (line[i] == '\0')
				print_error("The line was not well written. Please try again.");
		}
		else if (line[i] == 39)//'
		{
			i++;
			while (line[i] && line[i] != 39)
			{
				if (line[i] == 92 && i < (int)ft_strlen(line) - 1)
					i++;
				i++;//in this condition, we can also add a string to catch what's inside the quotes
			}
			if (line[i] == '\0')
				print_error("The line was not well written. Please try again.");
		}
		i++;
	}
}


//you have to check that in the line read, all the quotes are closed
//and the end of the line is not a PIPE
//=>Otherwise we gave error

/*int	print_error(char *str)
{
	perror(str);
	exit(1);
}*/

// PREVIOUS PREVIOUS PREVIOUS

/*int	find_next_quote(char *line, int *counter, int i, int ch)
{
	int	index;

	index = 0;
	*counter += 1;
	if (line[i] == ch)
	{
		index++;
		while (line[index] && line[index] != ch)
			index++;
	}
	//index++;
	if (line[index] == ch)
		*counter += 1;
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
			i += find_next_quote(line, &simple_quotes, i, 39);	
		if (line[i] == 34)//34 refers to " in the ascii table
			i += find_next_quote(line, &double_quotes, i, 34);
		i++;
	}
	if (simple_quotes % 2 == 0 || double_quotes % 2 == 0)// ||
	//	line[i] == '|' || line[i] == '>' || line[i] == '<')
	{
		printf("The line was not well written. Please try again.");
		return (1);
	}
	printf("everything's good");
	return (0);
	// Here's a function that looks for a pipe character and then continues searching to find any letter character
}*/
