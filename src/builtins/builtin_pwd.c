/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:47:49 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/19 10:58:27 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_mini *mini)//to free after having used it
{
	t_env_lst	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (mini->pwd && mini->old_pwd)
			break ;
		if (ft_strncmp(tmp->key, "PWD", 3) == 0)
		{
			if (mini->pwd)
                free(mini->pwd);
			mini->pwd = ft_strdup(tmp->value);
		}
		if (ft_strncmp(tmp->key, "OLD_PWD", 3) == 0)
		{
			if (mini->old_pwd)
				free(mini->old_pwd);
			mini->old_pwd = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
	if (mini->pwd == NULL)
	{
		char	*buffer = NULL;
		buffer = getcwd(NULL, 0);
		//if (buffer == NULL);
		mini->pwd = ft_strdup(buffer);
		mini->old_pwd = ft_strdup(buffer);
		free(buffer);
	}
	return (EXIT_SUCCESS);
}

int	builtin_pwd(t_mini *mini)
{
	if (mini->pwd != NULL && chdir(mini->pwd) == -1)
	{
		ft_putendl_fd(mini->pwd, 1);
		free(mini->pwd);
		mini->pwd = ft_strdup(mini->old_pwd);
		//chdir(mini->pwd);
	}
	else
		ft_putendl_fd(mini->pwd, 1);
	return (EXIT_SUCCESS);
}
