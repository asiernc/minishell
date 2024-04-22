/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:49:26 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/22 17:57:10 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check num pairs or no of quotes
//

int	lexer(char *str)
{
	t_lexer		lexer;
	int			i;
	char	**line;

	//line = readline("minihell🔥 >");
	line = ft_split(str, ' ');
	i = 0;
	while (line[i])
	{
		read_operators(line[i]);
		i++;
	}
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

