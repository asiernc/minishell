/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:59:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/27 18:37:34 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we will receive our command line as a char **str such as mini->cmd->str
//for example, if the command line is: echo my name is simon > outfile
//we manage: [[echo], [my], [name], [is], [simon]]
//index are:	 0      1      2      3      4
//in this command line, there is nothing to expand. We just have to call for 
//echo giving it the right str which should be "my name is simon"

//but if the command line is: echo "'my name is $USER'" > outfile
//we manage: [[echo], ['my name is $USER']
//index are:	 0              1
//there is str[1] to expand due to $USER. We have to call for
//the expand_the_line function that should return: 'my name is $login'

//this function checks if we have to expand the line or we just have to write it 
int	check_before_expansion(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0 && str[i] == '$' && str[i - 1] != BACKSLASH)
		{
			if (variable_existence(mini, str, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

//now for example if we have: echo "$USER""this is a test"
//we received it as: [[echo], ["$USER""this is a test"]]
//index are:             0              1
//the result has to be: loginthis is a test
//so we have to remove the doubles quotes

int	return_index_for_next_quote(char c, char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != c)
		i++;
	j++;
//	if (j != (int)ft_strlen(str) - 1)
//		return (j);
	return (j);
}

//34 in the ascii table <=> " 
//how to create a function that remove the quotes ?
//if we are in double quotes => we have to know where are the other double 
//quotes that closes the current quotes.
//we supposed that the quotes are closed => if we found one, there will be another one
int	about_quotes(char *str)
{
	int	i;
	int	k;

	i = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE && i + 1 < (int)ft_strlen(str))
		{
			k = return_index_for_next_quote((char)34, str, i + 1); 	
			printf("for double quotes k = %i\n", k);
		}
		else if (str[i] == QUOTE && i + 1 < (int)ft_strlen(str))
		{
			k = return_index_for_next_quote((char)39, str, i + 1); 	
			printf("k = %i\n", k);
		}
		i++;
	}
	return (0);
}

//we want a function that checks if we are in a simple quotes or not
/*int	in_simple_quote(char *str)
{
	while (str[i]
}*/
