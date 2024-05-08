/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:30:58 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/06 20:35:06 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *new_cmd(char **str, int num_redirections, t_lexer *redirections)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
   	if (!new)
		return (0);
	new->str = str;
   	new->builtin = str[0]; // find_builtin(str[0]) works well
   	new->hdoc_filename = NULL;
	new->num_redirections = num_redirections;
   	new->redirections = redirections;
	new->next = NULL;
	return (new);
}

void	ft_node_add_back_parser(t_cmd **lst, t_cmd *node)
{
	t_cmd *tmp;

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

int		lst_size_cmd(t_mini *mini)
{
	int	len;
	t_cmd	*tmp;

	len = 1;
	tmp = mini->cmd;
	while (tmp->next)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

// no hay malloc en parser!
void	lst_clear_parser(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp =  (*lst)->next;
		free(lst);
		*lst = tmp;
	}
	*lst = NULL;
}
