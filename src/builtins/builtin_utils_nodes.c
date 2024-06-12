/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:32:02 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/12 13:50:09 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back_builtin(t_builtin **lst, t_builtin *new)
{
	t_builtin	*tmp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

//to test
void	print_list(t_builtin **lst_env)
{
	int	i;

	i = 1;
	printf("list memory adress [%p]\n", lst_env);
	while (*lst_env)
	{
		printf("--------node%i--------\n", i);
		printf("memory adress [%p]\n", *lst_env);
		printf("key: %s\n", (*lst_env)->key);
		printf("value: %s\n", (*lst_env)->value);
		printf("index: %i\n", (*lst_env)->index);
		i++;
		*lst_env = (*lst_env)->next;
	}
}

int	ft_lstsize_builtin(t_builtin *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

