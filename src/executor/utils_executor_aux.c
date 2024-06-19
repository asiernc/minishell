/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:47:43 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/19 17:08:01 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_paths(char **str)
{
	int	i;

	if (!str || *str == NULL)
		return ;
	i = -1;
	while (str[++i])
	{
		free(str[i]);
	}
	free(str);
	str = NULL;
}
