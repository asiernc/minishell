/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/14 16:41:58 by simarcha         ###   ########.fr       */
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
			if (!(i == 0 && (str[i] == '-' || str[i] == '+')))
				return (0);
		}
	}
    printf("this is a 0\n");
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
    free(str);
	return (2);
}

static int	check_exit_many_arguments(char *str)
{
	if (ft_isdigit_and_signs(str) == 0)
		return (numeric_argument_required(str));
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("shelldone: exit", STDERR_FILENO);
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		return (1);
	}
}

int	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	char	*str1;
	char	*str2;
    int     exit_code;
	
    str1 = NULL;
    str2 = NULL;

	if (cmd->str && cmd->str[1])
	{
        str1 = ft_strdup(cmd->str[1]);
        if (cmd->str[2])
		    str2 = ft_strdup(cmd->str[2]);
	}
    //free_mini(mini);
	printf("str1 memory address %p && str1 = _%s_\n", str1, str1);
//	printf("cmd->str1 memory address %p && cmd->str[1] = _%s_\n", cmd->str[1], cmd->str[1]);
    printf("str2 memory address %p && str2 = _%s_\n", str2, str2);
//	printf("cmd->str1 memory address %p && cmd->str[2] = _%s_\n", cmd->str[2], cmd->str[2]);
	if (str2)
	{
		if (check_exit_many_arguments(str1) == 2)
			return (free_mini(mini), free(str2), exit(2), 2);
        else
            return (free_elements(str1, str2), 1);
	}
	if (str1)
	{
		if (ft_isdigit_and_signs(str1) == 0)
			return (free_mini(mini), exit(numeric_argument_required(str1)), 2);
		else
		{
            printf("l.107");
			if (check_zero(str1) == 1)
				return (free_mini(mini), free_elements(str1, str2), exit(0), 0);
            exit_code = ft_atoi(str1) % 256;
            printf("exit_code = %i\n", exit_code);
            free_elements(str1, str2);
			return (free_mini(mini), exit(exit_code), exit_code);
		}
	}
	return (free_mini(mini), free_elements(str1, str2),
		exit(g_global_var.error_code), g_global_var.error_code);
}
