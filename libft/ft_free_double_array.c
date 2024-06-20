/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:53:12 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/20 13:30:38 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_array(char ***str)
{
	int	i;
	int	counter;

	if (str == NULL || *str == NULL)
		return ;
	i = 0;
	while ((*str)[i])
		free((*str)[i++]);
	free(*str);
	*str = NULL;
}
