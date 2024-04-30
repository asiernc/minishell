/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/30 19:05:25 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct	s_builtin
{
	char				*key;//the name of the variable in env
	char				*value;
	int					index;//the index of the node
//	int					checker;//to check if the builtin is ENV or EXPORT
	struct s_builtin	*next;
}				t_builtin;//for ENV and EXPORT builtins

t_builtin	*ft_lstnew_builtin(char *str, int i);
char		*get_value_from_env(char *str);
void		print_list(t_builtin **lst_env);
void		ft_lstclear_builtin(t_builtin **lst);
t_builtin	*init_builtin_node(char **env);
int			ft_lstsize_builtin(t_builtin *lst);

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

//on veut comparer le premier noeud de la liste avec le suivant
//si le resultat du strcmp est negatif, alors on swap les deu neouds de la liste
//et on recommence au debut de la liste
//sinon on itere au suivant
static void	swap(t_builtin **lst)
{
	t_builtin	*first;
	t_builtin	*second;
	t_builtin	*tmp;

	if (*lst == NULL || (*lst)->next == NULL)
		return ;
	first = *lst;
	second = (*lst)->next;
	tmp = first;
	first->next = second->next;
	second->next = first;
	*lst = second;
}

t_builtin	*sort_ascii(t_builtin *unsorted_lst)
{
	t_builtin	*tmp;
	int			i;

	tmp = unsorted_lst;
	while ()
	{
		while (unsorted_lst && unsorted_lst->next)
		{
			if (ft_strcmp(unsorted_lst->key, unsorted_lst->next->key) < 0)
			{
				swap(&unsorted_lst);
				sort_ascii(unsorted_lst);
			}
			unsorted_lst = unsorted_lst->next;
		}
	}
	return (unsorted_lst);
}

void	builtin_export(char **env)
{
	t_builtin	*lst_export;
	t_builtin	*tmp;

	lst_export = create_builtin_lst(env);
	if (!lst_export)
		perror("error creating the list for the env");
	print_list(&lst_export);
//	lst_export = sort_ascii(lst_export);
	tmp = lst_export;
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	ft_lstclear_builtin(&lst_export);
}

//in this function, str refers to the new export variable. ie: 'abc=test'
void	add_export_variable(t_builtin *lst, char *str)
{
	t_builtin	*new_node;
	int			lst_size;

	lst_size = ft_lstsize_builtin(lst);
	new_node = ft_lstnew_builtin(str, lst_size - 1);
	if (!new_node)
		return (NULL);
	ft_lstadd_back_builtin(&lst, new_node);
}

int	main(int argc, char **argv, char **env)
{
	builtin_export(env);
	argc = 0;
	argv[0] = "./a.out";
	printf("%lu\n", sizeof(t_builtin));
	return (0);
}
