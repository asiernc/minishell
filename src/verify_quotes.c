/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:58:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/23 14:16:51 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//you have to check that in the line read, all the quotes are closed
//and the end of the line is not a PIPE
//=>Otherwise we gave error

int	print_error(char *str)
{
	perror(str);
	exit(1);
}

void	check_quotes(char *line)
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
		i++;
	}
	i--;
	if (simple_quotes_counter % 2 == 1 || double_quotes_counter % 2 == 1 ||
		line[i] == '|' || line[i] == '>' || line[i] == '<')
		print_error("The line was not well written. Please try again.");
//	printf("everything's good");
}

int	main(void)
{
	print_error("write something");
	return (0);
}
