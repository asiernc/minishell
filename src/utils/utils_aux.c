/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:07:20 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/19 17:05:40 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_lst_env(t_mini *mini)
{
	t_env_lst	*tmp;
	int			i;
	char		*joined_value;
	char		*temp;

	tmp = mini->env;
	mini->env_cpy = (char **)malloc(
			(ft_lstsize_builtin(mini->env) + 1) * sizeof(char *));
	if (!mini->env_cpy)
		print_error(mini, 2);
	i = 0;
	while (tmp)
	{
		joined_value = NULL;
		if (tmp->value != NULL)
		{
			temp = ft_strjoin("=", tmp->value);
			if (!temp)
			{
				ft_free_double_array(&mini->env_cpy);
				print_error(mini, 2);
			}
			joined_value = ft_strjoin(tmp->key, temp);
			free(temp);
			if (!joined_value)
			{
				ft_free_double_array(&mini->env_cpy);
				print_error(mini, 2);
			}
		}
		else
		{
			joined_value = ft_strdup(tmp->key);
			if (!joined_value)
			{
				ft_free_double_array(&mini->env_cpy);
				print_error(mini, 2);
			}
		}
		mini->env_cpy[i] = joined_value;
		tmp = tmp->next;
		i++;
	}
	mini->env_cpy[i] = NULL;
}
