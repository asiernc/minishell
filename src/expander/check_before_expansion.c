/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:59:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/28 19:20:21 by simarcha         ###   ########.fr       */
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
int	is_expansion_required(t_mini *mini, char *str)
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
//we suppose that the string received has been checked to have closed quotes
int	return_position_next_quote(char c, char *str, int i)
{
//	i++;//to forget the first quote
	while (str[i] && str[i] != c)
		i++;
	printf("i memory adress = %p\ni = %i\n", &i, i);
	return (i);
}

//we want a function that checks if we are in a simple quotes or not
int	we_are_in_simple_quote(char character)
{
	static int	quote_counter = 0;

	if (character == 39)
		quote_counter++;
	if (quote_counter % 2 == 0)
		return (0);
	return (1);
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
	
	int		check;

	i = 0;
	aux = ft_strdup("");//⚠️  malloc ⚠️ 
	if (!aux)
		print_error(mini, 2);
	check = 0;
	while (str[i])
	{
//		printf("2\n");
/*		if (str[i] == QUOTE && i + 1 < (int)ft_strlen(str))
		{
			if (quote_counter % 2 == 0)
*/		while (we_are_in_simple_quote(str[i]) == 1)
		{
//				printf("we are in simple quotes\n");
//				printf("3\n");
				k =	return_position_next_quote(QUOTE, str, i + 1); 	
//				printf("for simple quotes at index %i, k = %i\n", i, k);
				tmp = ft_substr(str, i + 1, k - (i + 1));//⚠️  malloc ⚠️ 
//				printf("tmp for substring result memory adress = %p\ntmp = _%s_\n", &aux, aux);
				if (check == 1)
					free(result);
//				printf("aux memory adress = %p\naux = _%s_\n", &aux, aux);
//				printf("tmp memory adress = %p\ntmp = _%s_\n", &tmp, tmp);
				result = ft_strjoin(aux, tmp);
				check = 1;
				free(aux);
				free(tmp);
				aux = ft_strdup(result);
		}
		printf("at the end of the simple quote: result = %s\n", result);
//			free(result);//⚠️  you have to free result once used
//		else if (str[i] == DQUOTE && i + 1 < (int)ft_strlen(str))
//		{
//			printf("we are in double quotes\n");
			k = return_position_next_quote(DQUOTE, str, i + 1); 	
//			printf("for double quotes at index %i, k = %i\n", i, k);
			tmp = ft_substr(str, i + 1, k - (i + 1));//⚠️  malloc ⚠️ 
//			printf("result = %s\n", result);
			if (check == 1)
				free(result);
//			printf("aux memory adress = %p\naux = _%s_\n", &aux, aux);
//			printf("tmp memory adress = %p\ntmp = _%s_\n", &tmp, tmp);
			result = ft_strjoin(aux, tmp);
			check = 1;
			free(aux);
			free(tmp);
			aux = ft_strdup(result);
//		}
		i++;
	}
//	printf("result = %s\n", result);
	return (free(aux), 0);
}

char	*quit_single_quotes(t_mini *mini, char *str)
{
	int		i;
	int		k;
	char	*result;
	char	*tmp;
	char	*aux;
	
	int		check;
	i = 0;
	aux = ft_strdup("");//⚠️  malloc ⚠️ 
	if (!aux)
		print_error(mini, 2);
	check = 0;
	while (str[i])
	{
		while (we_are_in_simple_quote(str[i]) == 1)

		{
			k =	return_position_next_quote(QUOTE, str, i + 1);
			tmp = ft_substr(str, i + 1, k - (i + 1));//⚠️  malloc ⚠️ 
			if (check == 1)
				free(result);
			result = ft_strjoin(aux, tmp);
			check = 1;
			free(aux);
			free(tmp);
			aux = ft_strdup(result);
//			free(result);//⚠️  you have to free result once used
		}
		//si on trouve un dollar et que le caractere anterieur n'etait pas un BACKSLASH
		if (i > 0 && str[i] == '$' && str[i - 1] != BACKSLASH)
		{
			//if (variable_existence(mini, str, i) == 1)
		}
		printf("result = %s\n", result);
		i++;
	}
	return (free(aux), result);
}

//we have a string like this: echo 'this' "is" '''a' "test" '$from' "$USER"
//the result has to be      : this is a test $from simarcha

//we have the function that partially remove the single string
//but it doesn't work if we have a mix of single and double quotes

//this function returns the situation about being or inside single quotes
//or inside double quotes, or inside none of both.
int	check_the_situation(char c, int *lead)
{
/*	if (c == QUOTE && lead == 0)
		lead = 1;
	else if (c == QUOTE && lead == 1)
		lead = 0;
	else if (c == DQUOTE && lead == 0)
		lead = 2;
	else if (c == DQUOTE && lead == 2)
		lead = 0;*/
	if (*lead == 0)
	{
		if (c == QUOTE)
			*lead = 1;
		else if (c == DQUOTE)
			*lead = 2;
	}
	else if (*lead == 1)
	{
		if (c == QUOTE)
			*lead = 0;
	}
	else if (*lead == 2)
	{
		if (c == DQUOTE)
			*lead = 0;
	}
	return (*lead);
}

char	*final_expansion(t_mini *mini, char *str)
{
	int		i;
	int		lead;
	int		start;
	char	*string;
	char	*result;

	i = 0;
	lead = 0;
	printf("str[i] = %c\n", str[i]);
//	printf("lead = %i\n"
	printf("lead memory adress = %p\nlead = %i\n", &lead, lead);
	while (str[i])
	{
		printf("1\n");
		if (check_the_situation(str[i], &lead) == 1)//currently in simple quotes
		{
			printf("1.1\n");
			start = i;
			while (str[i] && check_the_situation(str[i], &lead) == 1)
				i++;
			string = ft_substr(str, start + 1, i - (start + 1));//⚠️  malloc ⚠️  to protect && to free
			if (!string)
				print_error(mini, 2);
			//appelle une fonction qui quittes les singles quotes
		}
		else
		{
			printf("3\n");
			start = i;
			while (str[i] && check_the_situation(str[i], &lead) != 1)
				i++;
			string = ft_substr(str, start + 1, i - (start + 1 + 1));//⚠️  malloc ⚠️  to protect && to free
			if (!string)
				print_error(mini, 2);
			printf("string = %s\n", string);
			result = expand_the_line(mini, string);//⚠️  malloc ⚠️  to protect && to free
			if (!result)
				print_error(mini, 2);
			// on va copier les characters
			// si on trouve un $ et que l'on realise que c'est une env
			//		on expand
		}
		i++;
	}
	return (result);
}
