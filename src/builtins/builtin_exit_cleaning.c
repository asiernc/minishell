/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_cleaning.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:28:38 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/14 15:58:21 by simarcha         ###   ########.fr       */
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
	ft_free_double_array(mini->env_cpy);
	ft_lstclear_builtin(&mini->env);
	if (mini->pwd)
		free(mini->pwd);
	if (mini->pipes)
		free(mini->pid);
}
