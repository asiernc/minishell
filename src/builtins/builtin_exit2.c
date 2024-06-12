/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:37:51 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/12 16:18:50 by anovio-c         ###   ########.fr       */
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

static int	check_str_exit(char *str)
{
	// si es una expansion, a exit le da igual, sale con 0
	//if (str[0] == '$')
	//	return (0);
	int	exit_code;
	int	i;

	i = -1;
	while (str[++i])
		if (!(ft_isdigit(str[i])) || (str[0] != '-' || str[0] != '+'))
			return (-1);
	if (*str != '0' && ft_atoi(str) == 0)
		return (-1);
	exit_code = ft_atoi(str);
	if (exit_code >= 0 && exit_code <= 255)
		return (exit_code);
	else
		return (exit_code % 256);
}

int	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	//char	*tmp;
	int		exit_code;

	mini->original_env = NULL;
	//free_mini(mini);
	if (cmd->str[1] && cmd->str[2])
	{
		//bash: exit: too many arguments
		ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
		ft_putendl_fd("too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	//tmp = ft_strdup(cmd->str[1]);
	//ft_lstclear_builtin(&mini->env);
	free_mini(mini);
	if (cmd->str[1])
	{
		exit_code = check_str_exit(cmd->str[1]);
		if (exit_code == -1)
		{
			ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->str[1], STDERR_FILENO);
			print_error(mini, 10);
		}
		else
			exit(exit_code);
	}
	exit(0);
	return (EXIT_SUCCESS);
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

static int	check_str_exit(char *str)
{
	int	exit_code;
	//int	i;

	printf("NUM %d\n", ft_atoi(str));
	//if (ft_strcmp(str, "-0") == 0 || ft_strcmp(str, "+0") == 0)
	//	exit (0);
	//i = -1;
	//while (str[++i])
	//{
		//if ((str[0] != '-' || str[0] != '+'))
		//{
		//	if (ft_isdigit(str[i]) == 0)
		if (ft_isdigit_and_signs(str) == 1)
				return (-1);
		//}
	//}
	if (check_zero(str) == 0 && ft_atoi(str) == 0)
		return (-1);
	exit_code = ft_atoi(str);
//	if (exit_code >= 0 && exit_code <= 255)
//		return (exit_code);
//	else
		return (exit_code % 256);
}


static int	ft_isdigit_and_signs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			if (i != 0 && (str[i] != '-' || str[i] != '+'))
				return (0);
		}
	}
	return (1);
}

static int	check_str_exit(char *str)
{
	int	exit_code;

    if (ft_isdigit_and_signs(str) == 1)
		return (-1);
	exit_code = ft_atoi(str);
	if (exit_code >= 0 && exit_code <= 255)
		return (exit_code);
	else
		return (exit_code % 256);
}

/////////////////////////////////////////////////





////////////////////////////////////////////////

int	check_exit_many_arguments(t_cmd *cmd)
{
	if (!ft_isdigit_and_signs(cmd->str[1]))
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
	
	if (cmd->str[1] && cmd->str[2])
		return (exit(check_exit_many_arguments(cmd)), check_exit_many_arguments(cmd));
	free_mini(mini);
	if (cmd->str[1])
	{
		exit_code = check_str_exit(cmd->str[1]);
		if (exit_code == -1)
		{
			ft_putstr_fd("shelldone: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->str[1], STDERR_FILENO);
			exit(2);
		}
		else
			exit(exit_code);
	}
	exit(0);
	return (EXIT_SUCCESS);
}