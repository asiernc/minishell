/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/12 17:26:30 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_expander(t_mini *mini, t_cmd *cmd)
{
	t_cmd	*tmp;
	t_lexer	*tmp2;

	tmp = cmd;
	tmp->str = expand_cmd_line(mini, tmp->str);
	tmp2 = cmd->redirections;
	while (tmp2)
	{ 
		if (tmp2->token != HDOC)
			tmp2->str = expand_str_line(mini, tmp2->str);
		tmp2 = tmp2->next;
	}
}

// expand cmd line. only cmd flags and args of the cmd
char	**expand_cmd_line(t_mini *mini, char **str)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	while (str[i])
	{
		new = final_expansion(mini, str[i]);
		free(str[i]);
		str[i] = new;
		i++;
	}
	return (str);
}

// expand str==> filename
char	*expand_str_line(t_mini *mini, char *str)
{
	char	*new;

	new = NULL;
	new = final_expansion(mini, str);
	free(str);
	str = new;
	return (str);
}
