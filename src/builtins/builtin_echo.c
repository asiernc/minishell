/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/16 18:49:18 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we want to count the lines of the array
int	lines_counter(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

static int	builtin_echo_flag_n(t_mini *mini, t_cmd *command, int i, int wc)
{
	while (command->str[i])
	{
		if (write(1, command->str[i], ft_strlen(command->str[i])) == -1)
			return (print_error(mini, 0, 0), 0);//keycode = write has failed
		if (i < wc - 1)
			if (write(1, " ", 1) == -1)
				return (print_error(mini, 0, 0), 0);//keycode = write has failed
		i++;
	}
	return (1);
}

int	builtin_echo(t_mini *mini, t_cmd *command)
{
	int	wordcount;
	int	i;

	wordcount = lines_counter(command->str);
	i = 1;
	if (command->str[1]	&& ft_strcmp_simple(command->str[1], "-n") == 0)
		return (builtin_echo_flag_n(mini, command, 2, wordcount));
	else
	{
		while (command->str[i])
		{
			if (write(1, command->str[i], ft_strlen(command->str[i])) == -1)
				print_error(mini, 0, 0);//keycode = write has failed
			if (i < wordcount - 1)
				if (write(1, " ", 1) == -1)
					return (print_error(mini, 0, 0), 0);//keycode = write has failed
			i++;
		}
		if (write(1, "\n", 1) == -1)
			return (print_error(mini, 0, 0), 0);//keycode = write has failed
	}
	return (1);
}
