/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:47:44 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/24 17:22:40 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	list_add_node(t_lexer **lexer_list, t_operator token, char *str)
{
	t_lexer	*node;

	node = ft_new_node(str, token);
	if (!node)
		return (1);
	ft_node_add_back(lexer_list, node);
	return (0);
}

t_lexer	*ft_new_node(char *str, int token)
{
	t_lexer		*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->str = str;
	new->token = token;
	new->next = NULL;
	return (new);
}

void	ft_node_add_back(t_lexer **lst, t_lexer *node)
{
	t_lexer	*tmp;

	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_lexer	*clear_one_node(t_lexer **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	del_first_node(t_lexer **lst)
{
	t_lexer	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	clear_one_node(&tmp);
}

/*void	delone_lexer(t_lexer **lst)
{
	t_lexer	*tmp;

	tmp = lst->next;
	free(*lst);
*/
