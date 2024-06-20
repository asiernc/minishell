/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:30:10 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/20 18:09:32 by simarcha         ###   ########.fr       */
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
	if (mini->pipes)
		free(mini->pid);
	ft_free_double_array(&mini->env_cpy);
	ft_lstclear_builtin(&mini->env);
	free(mini->env);
	free(mini->pwd);
	free(mini->old_pwd);
}

int	builtin_exit(t_mini *mini, t_cmd *cmd, t_var g_var)
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
		exit(g_var.error_code), g_var.error_code);
}
