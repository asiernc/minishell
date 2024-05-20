/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:25:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/14 13:04:40 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//**head refers to the env builtin list
//the str refers to the variable to remove (for example PWD)
//this function is basically remove a node
void	builtin_unset(t_builtin **head, char *str)
{
	t_builtin	*current;
	t_builtin	*previous;

	previous = NULL;
	current = *head;
	if (*head == NULL)
		return ;
	while (current)
	{
		if (ft_strlen(current->key) == ft_strlen(str) &&
			ft_strcmp_simple(current->key, str) == 0)
		{
			if (previous == NULL)
			{
				*head = current->next;
				return ;
			}
			else
				previous->next = current->next;
			return (free(current->key), free(current->value), free(current));
		}
		previous = current;
		current = current->next;
	}
}
