/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/14 09:52:45 by asiercara        ###   ########.fr       */
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

static int	check_exit_many_arguments(char *str)
{
	if (ft_isdigit_and_signs(str) == 0)
		return (numeric_argument_required(str));
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (2);
	}
}

int	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	char	*str;
	char	*str2;
	
	str = ft_strdup(cmd->str[1]);
	if (cmd->str && cmd->str[1] && cmd->str[2])
		str2 = cmd->str[2];
	//mini->original_env = NULL;
	free_mini(mini);
	if (str && str2)
	{
		return (exit(check_exit_many_arguments(str)),
			check_exit_many_arguments(str));
	}
	if (str)
	{
		if (ft_isdigit_and_signs(str) == 0)
			return (exit(numeric_argument_required(str)), 2);
		else
		{
			if (check_zero(str) == 1)
				return (exit(0), 0);
			return (exit(ft_atoi(str) % 256),
				ft_atoi(str) % 256);
		}
	}
	return (exit(g_global_var.error_code), g_global_var.error_code);
}
