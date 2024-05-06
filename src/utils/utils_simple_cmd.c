/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:30:58 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/02 11:13:20 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmd *new_simple_cmd(char **str, int num_redirections, t_lexer *redirections)
{
	t_simple_cmd	*new;

	new = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
   	if (!new)
		return (0);
	new->str = str;
   	new->builtin = str[0]; // find_builtin(str[0]) works well
   	new->hd_filename = NULL;
	new->num_redirections = num_redirections;
   	new->redirections = redirections;
	new->next = NULL;
	return (new);
}

void	ft_node_add_back_parser(t_simple_cmd **lst, t_simple_cmd *node)
{
	t_simple_cmd *tmp;

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

int		lst_size_simple_cmd(t_mini *mini)
{
	int	len;
	t_simple_cmd	*tmp;

	len = 1;
	tmp = mini->simple_cmd;
	while (tmp->next)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

// no hay malloc en parser!
void	lst_clear_parser(t_simple_cmd **lst)
{
	t_simple_cmd	*tmp;

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