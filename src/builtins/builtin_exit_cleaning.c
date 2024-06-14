/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_cleaning.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:28:38 by simarcha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/14 14:40:30 by simarcha         ###   ########.fr       */
=======
/*   Updated: 2024/06/14 13:04:54 by simarcha         ###   ########.fr       */
>>>>>>> ea841ed77f9ec91e651696a585791536c381db1e
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
