/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/17 11:53:25 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_elements(char *str1, char *str2)
{
	if (str1)
	{
		if (str2)
			free(str2);
		free(str1);
	}
}

void	free_mini(t_mini *mini)
{
	if (mini->cmd)
		lst_clear_cmds(&mini->cmd);
	if (mini->line)
		free(mini->line);
	if (mini->pid)
		free(mini->pid);
	ft_free_double_array(&mini->env_cpy);
	ft_lstclear_builtin(&mini->env);
	free(mini->env);
	if (mini->pwd && *mini->pwd)
		free(mini->pwd);
	if (mini->old_pwd && *mini->old_pwd)
		free(mini->old_pwd);
}

int	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	char	*str1;
	char	*str2;

	str1 = NULL;
	str2 = NULL;
	if (cmd->str && cmd->str[1])
	{
		str1 = ft_strdup(cmd->str[1]);
		if (cmd->str[2])
			str2 = ft_strdup(cmd->str[2]);
	}
	if (str2)
	{
		if (check_exit_many_arguments(str1) == 2)
			return (free_mini(mini), free(str2), exit(2), 2);
		else
			return (free_elements(str1, str2), 1);
	}
	if (str1)
		return (exit_with_one_argument(mini, str1, str2));
	return (free_mini(mini), free_elements(str1, str2),
		exit(g_global_var.error_code), g_global_var.error_code);
}
