/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_cleaning.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:28:38 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/12 18:29:00 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mini(t_mini *mini)
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