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

/*int	find_pwd(t_mini *mini)//to free after having used it
{
	char	**env_cpy;
	int		i;
	char	*path_prefix;
	char	*result;

	env_cpy = mini->original_env;
	path_prefix = ft_strdup("PWD=");
	if (!path_prefix)
		print_error(mini, 5); //Allocation memory error
	i = 0;
	while (env_cpy[i])
	{
		if (ft_strncmp(env_cpy[i], path_prefix, ft_strlen(path_prefix)) == 0)
		{
			free(path_prefix);
			result = ft_strdup(env_cpy[i] + 4);
			if (!result)
				print_error(mini, 5);
			mini->pwd = result;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}*/

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