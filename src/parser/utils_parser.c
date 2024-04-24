/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:01:02 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/24 16:03:17 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipes(t_mini *mini)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (mini->line[++i])
		if (mini->line[i] == '|')
			count++;
		//i++;
	mini->pipes = count;
}
