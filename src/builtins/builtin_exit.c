/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/13 10:34:47 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	check_zero(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '0')
		{
			if (i != 0 && (str[i] != '-' || str[i] != '+'))
				return (0);
		}
	}
	return (1);
}

static int	ft_isdigit_and_signs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if (i != 0 && (str[i] != '-' || str[i] != '+'))
				return (0);
		}
	}
	return (1);
}

static int	numeric_argument_required(char *str)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	return (2);
}

static int	check_exit_many_arguments(t_cmd *cmd)
{
	if (ft_isdigit_and_signs(cmd->str[1]) == 0)
		return (numeric_argument_required(cmd->str[1]));
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->str[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (2);
	}
}

int	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	mini->original_env = NULL;
	if (cmd->str[1] && cmd->str[2])
	{
		return (exit(check_exit_many_arguments(cmd)),
			check_exit_many_arguments(cmd));
	}
	free_mini(mini);
	if (cmd->str[1])
	{
		if (ft_isdigit_and_signs(cmd->str[1]) == 0)
			return (exit(numeric_argument_required(cmd->str[1])), 2);
		else
		{
			if (check_zero(cmd->str[1]) == 1)
				return (exit(0), 0);
			return (exit(ft_atoi(cmd->str[1]) % 256),
				ft_atoi(cmd->str[1]) % 256);
		}
	}
	return (exit(g_global_var.error_code), g_global_var.error_code);
}
