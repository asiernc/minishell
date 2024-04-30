/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_lst_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:32:02 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/30 10:36:24 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct	store_env
{
	char				*key;//the name of the variable in env
	char				*value;
	struct store_env	*next;
}				t_env;

char	*get_key_from_env(char *str);
char	*get_value_from_env(char *str);

t_env	*ft_lstnew_env(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = get_key_from_env(str);
	if (!node->key)
		return (free(node), NULL);
	node->value = get_value_from_env(str);
	if (!node->value)
		return (free(node), NULL);
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

//to test
void	print_list(t_env **lst_env)
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
		i++;
		*lst_env = (*lst_env)->next;
	}
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
	lst = NULL;
}
