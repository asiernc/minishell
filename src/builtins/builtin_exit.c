/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/12 16:46:03 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	free_mini(t_mini *mini)
{
	ft_free_double_array(mini->env_cpy);
	ft_lstclear_builtin(&mini->env);
	//free(mini->line);
	//lst_clear_cmds(&mini->cmd);
	//free(mini->pwd);
	//free(mini->old_pwd);
	if (mini->pipes)
		free(mini->pid);
}


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
		if (ft_isdigit(str[i]) == 0)//if it's a letter (!= digit)
		{
			if (i != 0 && (str[i] != '-' || str[i] != '+'))//and the first is not a sign
				return (0);
		}
	}
	printf("is good digit_and_sign\n");
	return (1);
}

/*int	ft_isdigit_and_signs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') || str[0] == '-' || str[0] == '+')
			return (0);
		i++;
	}
	printf("is good digit_and_sign\n");
	return (1);
}*/

static int	check_str_exit(char *str)
{
	int	exit_code;

	if (check_zero(str) == 1)
		return (0);
	printf("is not 0\n");
	if (ft_isdigit_and_signs(str) == 1)
		return (-1);
	printf("is not digit and sign\n");
	exit_code = ft_atoi(str);
	return (exit_code % 256);
}

int	check_exit_many_arguments(t_cmd *cmd)
{
	if (ft_isdigit_and_signs(cmd->str[1]) == 0)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->str[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (2);
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
		ft_putendl_fd("too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
}

int	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	//char	*tmp;
	int		exit_code;

	mini->original_env = NULL;
	
	//free_mini(mini);
	printf("flag initial exit\n");
	if (cmd->str[1] && cmd->str[2])
	{
		printf("flag if there is two args for exit l.100\n");
		return (exit(check_exit_many_arguments(cmd)), check_exit_many_arguments(cmd));
	}
	//tmp = ft_strdup(cmd->str[1]);
	//ft_lstclear_builtin(&mini->env);
	printf("flag l.105\n");
	free_mini(mini);
	if (cmd->str[1])
	{
		printf("flag l.109\n");
		exit_code = check_str_exit(cmd->str[1]);
		if (exit_code == -1)
		{
			printf("flag if exit_code == -1 l.113\n");
			ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->str[1], STDERR_FILENO);
			exit(2);
		}
		else
		{
			printf("flag else l.120\n");
			exit(exit_code);
		}
	}
	printf("flag finish exit\n");
	exit(0);
	return (EXIT_SUCCESS);
}