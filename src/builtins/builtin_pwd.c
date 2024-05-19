/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:47:49 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/19 14:28:29 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//maybe it won't work if the user change the directory => to check
int	builtin_pwd(t_mini *mini)//to free after having used it
{
	char	**env_cpy;
	int		i;
	char	*path_prefix;
	char	*result;

	env_cpy = mini->env;
	path_prefix = ft_strdup("PWD=");
	if (!path_prefix)
		print_error(mini, mini->lexer, 5); //Allocation memory error
	i = 0;
	while (env_cpy[i])
	{
		if (ft_strncmp(env_cpy[i], path_prefix, ft_strlen(path_prefix)) == 0)
		{
			free(path_prefix);
			result = ft_strdup(env_cpy[i] + 4);
			if (!result)
				print_error(mini, mini->lexer, 5);
			ft_putendl_fd(result, 1);
			free(result);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
