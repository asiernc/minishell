/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:47:49 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/12 13:36:37 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pwd(t_mini *mini)//to free after having used it
{
	t_builtin	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 3) == 0)
		{
			mini->pwd = tmp->value;
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

int	builtin_pwd(t_mini *mini)
{
	ft_putendl_fd(mini->pwd, 1);
	return (EXIT_SUCCESS);
}
