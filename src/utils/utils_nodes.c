/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:47:44 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/26 12:57:19 by anovio-c         ###   ########.fr       */
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
	static unsigned int	i = 0;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->str = str;
	new->num_node = ++i;
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

int		lst_size_simple_cmd(t_mini *mini)
{
	int	len;
	t_simple_cmd	*tmp;

	len = 0;
	tmp = mini->simple_cmd;
	while (tmp->next)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int		lst_size(t_mini *mini)
{
	int	len;
	t_lexer	*tmp;

	tmp = mini->lexer;
	len = 0;
	while (tmp->next)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

t_simple_cmd *new_simple_cmd(char **str, int num_redirections, t_lexer *redirections)
{ 
	t_simple_cmd	*new;
   
	new = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
   	if (!new) 
		return (0); 
	new->str = str;
	//if (str[0] == builtn
   	new->builtin = 0; // identificar builtin
   	new->hd_filename = NULL; 
	new->num_redirections = num_redirections;
   	new->redirections = redirections;
	new->next = NULL; 
	return (new);
}

void delone_node(int num_del, t_lexer **lst)
{
	t_lexer *node; 
	t_lexer *prev;
	t_lexer *start;
	
	start = *lst;
	node = start;
	if ((*lst)->num_node == num_del)
	{
		del_first_node(lst);
		return ;
	}
	while (node && node->num_node != num_del)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	clear_one_node(&node);
	*lst = start;
}
