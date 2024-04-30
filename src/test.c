/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:34:50 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/30 18:36:30 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"

#include <stdlib.h>

typedef struct	s_test
{
	char				*str;
	int					index;
	struct s_builtin	*next;
}				t_test;

t_test	*ft_lstnew(char *str, int i)
{
	t_test	*node;

	node = malloc(sizeof(t_test));
	if (!node)
		return (NULL);
	node->str = str;
	node->index = i;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_test **lst, t_test *new)
{
	t_test	*tmp;

	if (!lst || !new)
		return ;
	else if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstclear(t_test **lst)
{
	t_test	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
		tmp = NULL;
	}
	lst = NULL;
}

void	print_list(t_test **lst)
{
	int	i;

	i = 1;
	printf("list memory adress [%p]\n", lst);
	while (*lst)
	{
		printf("--------node%i--------\n", i);
		printf("memory adress [%p]\n", *lst);
		printf("str: %s\n", (*lst)->str);
		printf("index: %i\n", (*lst_env)->index);
		*lst = (*lst)->next;
		i++;
	}
}

t_test	*create_list(char **argv)
{
	int		i;
	t_test	*new_node;
	t_test	*lst;

	i = 1;
	while (argv[i])
	{
		new_node = ft_lstnew(argv[i], i - 1);
		if (!new_node)
			return (NULL);	
		ft_lstadd_back(&lst, new_node);
		i++;
	}
	return (lst);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/*t_test	*sort_list_ascii(t_test *lst)
{
	t_test	*tmp;

	tmp = lst;
	while (lst && lst->next)
	{
		while (lst && lst->next)
		{
			if (ft_strcmp(lst->str, lst->next->str) < 0)
			{
				switch_nodes(lst);
				update_index(lst);
				tmp = lst;
			}
			lst = lst->next;
		}
		tmp = tmp->next;
	}
	return (lst);
}*/

int	main(int argc, char **argv)
{
	t_test	*my_lst;
	
	my_lst = create_list(argv);
	if (!my_lst)
		return (1);
	my_lst = sort_list_ascii(my_lst);
	print_list(&my_lst);
	argc = 0;
	return (0);
}
