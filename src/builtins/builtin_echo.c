/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/19 19:36:34 by simarcha         ###   ########.fr       */
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

//we have to check if the flag of the echo command is written in that way :
//-nnnnnnnnnnnnn -> that is also considered as correct
static int	check_flag(char *flag)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (flag[i])
	{
		if (flag[i] == '-' && i == 0)
		{
			i++;
			check = 1;
		}
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	if (check == 1 && i == (int)ft_strlen(flag))
		return (1);
	return (0);
}

static int	builtin_echo_flag_n(t_mini *mini, t_cmd *command, int i, int wc)
{
	while (command->str[i])
	{
		while (command->str[i] && (ft_strcmp_simple(command->str[i], "-n") == 0
				|| check_flag(command->str[i]) == 1))
			i++;
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
	if (command->str[i] && (ft_strcmp_simple(command->str[i], "-n") == 0
			|| check_flag(command->str[i]) == 1))
		return (builtin_echo_flag_n(mini, command, 2, wordcount));
	else if (command->str[i] && (ft_strcmp(command->str[i], "$?") == 0))
		//printf("%i\n", last_exit_status);
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
