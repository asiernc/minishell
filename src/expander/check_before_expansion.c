/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:59:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/28 13:10:33 by simarcha         ###   ########.fr       */
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
int	return_position_next_quote(char c, char *str, int i)
{
	i++;//to forget the first quote
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

//34 in the ascii table <=> " 
//how to create a function that remove the quotes ?
//if we are in double quotes => we have to know where are the other double 
//quotes that closes the current quotes.
//we supposed that the quotes are closed => if we found one, there will be another one
int	about_quotes(t_mini *mini, char *str)
{
	int		i;
	int		k;
	char	*result;
	char	*tmp;
	char	*aux;

	i = 0;
//	printf("1\n");
	aux = ft_strdup("");//⚠️  malloc ⚠️ 
	if (!aux)
		print_error(mini, 2);
//	printf("1.1\n");
	printf("aux memory adress = %p\naux = _%s_\n", &aux, aux);
	printf("i memory adress = %p\ni = %i\n", &i, i);
	printf("str[i] = %c\n", str[i]);
	while (str[i])
	{
//		printf("2\n");
		if (str[i] == QUOTE && i + 1 < (int)ft_strlen(str))
		{
//			printf("3\n");
			k = return_position_next_quote((char)39, str, i + 1); 	
			printf("for simple quotes at index %i, k = %i\n", i, k);
			tmp = ft_substr(str, i + 1, k - (i + 1));//⚠️  malloc ⚠️ 
			result = ft_strjoin(aux, tmp);
			free(aux);
			free(tmp);
			aux = ft_strdup(result);
		}
		else if (str[i] == DQUOTE && i + 1 < (int)ft_strlen(str))
		{
			k = return_position_next_quote((char)34, str, i + 1); 	
			printf("for double quotes at index %i, k = %i\n", i, k);
			result = ft_substr(str, i + 1, k - (i + 1));//⚠️  malloc ⚠️ 
			printf("result = %s\n", result);
			free(result);
		}
		i++;
	}
	printf("result = %s\n", result);
	return (free(aux), 0);
}

//we want a function that checks if we are in a simple quotes or not
/*int	in_simple_quote(char *str)
{
	while (str[i]
}*/
