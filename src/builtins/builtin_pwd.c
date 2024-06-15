/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:47:49 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/13 13:09:00 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_mini *mini)//to free after having used it
{
	t_env_lst	*tmp;

	if (mini->pwd != NULL)
		free(mini->pwd);
	tmp = mini->env;
	mini->pwd = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 3) == 0)
		{
			mini->pwd = tmp->value;
			break ;
		}
		/*if (ft_strncmp(tmp->key, "OLD_PWD", 3) == 0)
		{
			mini->old_pwd = ft_strdup(tmp->value);
			break ;
		}*/
		tmp = tmp->next;
	}
	if (mini->pwd == NULL)
		mini->pwd = getcwd(NULL, 0);
	return (EXIT_SUCCESS);
}

int	builtin_pwd(t_mini *mini)
{
	//if (!mini->pwd)
	//	mini->pwd = getcwd(NULL, 0);
	ft_putendl_fd(mini->pwd, 1);
	return (EXIT_SUCCESS);
}
