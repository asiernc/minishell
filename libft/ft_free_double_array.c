/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:53:12 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/20 17:09:36 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_free_double_array(char ***str)
{
    int i;

    if (str == NULL || *str == NULL)
        return;
    i = 0;
    while ((*str)[i])
        free((*str)[i++]);
    free(*str);
    *str = NULL;
}

//si falla mira eso con Linux
/*char	**free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	return (NULL);
}*/
