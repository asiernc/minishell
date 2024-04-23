/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:58:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/24 00:09:38 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"
#include <stdio.h>

//you have to check that in the line read, all the quotes are closed
//and the end of the line is not a PIPE
//=>Otherwise we gave error

/*int	print_error(char *str)
{
	perror(str);
	exit(1);
}*/

int	find_next_quote(char *line, int *counter, int i, int ch)
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
	if (simple_quotes % 2 == 1 || double_quotes % 2 == 1)// ||
	//	line[i] == '|' || line[i] == '>' || line[i] == '<')
	{
		printf("The line was not well written. Please try again.");
		return (1);
	}
	printf("everything's good");
	return (0);
	// Here's a function that looks for a pipe character and then continues searching to find any letter character
}

int	main(void)
{
	char str[50] = "echo 'hola 'm'undo''";

	check_quotes(str);
	//print_error("write something");
	return (0);
}
