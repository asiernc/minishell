/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:47:49 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/13 13:55:09 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_mini *mini)//to free after having used it
{
	t_builtin	*tmp;

	tmp = mini->env;
	while (mini->env)
	{
		if (ft_strncmp(mini->env->key, "PWD", 3) == 0)
		{
			mini->pwd = mini->env->value;
			return (EXIT_SUCCESS);
		}
		mini->env = mini->env->next;
	}
	mini->env = tmp;
	return (EXIT_FAILURE);
}

int	builtin_pwd(t_mini *mini)
{
	ft_putendl_fd(mini->pwd, 1);
	return (EXIT_SUCCESS);
}