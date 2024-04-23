/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:49:26 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/22 22:18:52 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check num pairs or no of quotes
//

int	lexer(t_mini *mini)
{
	int			i;
	char	**line;

	line = ft_split(str, ' ');
	i = 0;
	while (line[i])
	{
		read_operators(line[i]);
		i++;
	}
	return (0);
}

//check is_sace before calling thi function
void	read_operators(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str == "|")
		lexer.token = PIPE;
	else if (*str == "<")
	{
		if (*(str + 1) && *(str + 1) != "<")
			lexer.token = DOUBLE_GREATER;
		else
			lexer.token = GREATER;
	}
	else if (*str == ">")
	{
		if (*(str + 1) && *(str + 1) != ">")
			lexer.token = DOUBLE_LESS;
		else
			lexer.token = LESS;
	}
	else
		lexer.token = 0;
}

