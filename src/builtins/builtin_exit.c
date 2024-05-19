/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:08:54 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/19 15:37:25 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	if (cmd->str[1])
	{
		if (is_number(cmd->str[1]) == 0)
			return (print_error(mini, mini->lexer, 10), 255);
		exit(ft_atoi(cmd->str[1]) % 256);
	}
	exit(0);
	return (EXIT_SUCCESS);
}
