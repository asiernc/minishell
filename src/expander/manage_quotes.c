/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:49:37 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/21 19:54:50 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//we want a function to know if the expanded variable has to be expanded or not
//for example, if we have: echo '$test' => we don't have to expand it =>output: $test
//but if we have		 : echo "$test" => we have to expand it => output : content of test
//basically if the content is between simple quotes => we don't expand it
//else (there is no quotes or double quotes), we expand it

//we want to return a int to know if we have to expand it or not
//it means if we are in a double or a single quote
/*int	expand_or_not(t_mini *mini, char *str)
{
	int	check;
	int	i;

	check = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			if (check == 1)
				check = 0;
			else
				check = 1;
		}
		i++;
	}
	return (!check);
}

int	expand_or_not(char *str)
{
	int	i;
	int	sq_check;
	int	dq_check;

	i = 0;
	sq_check = 0;
	dq_check = 0;
	while (str[i])
	{
		if (str[i] == DQUOTE && sq_check == 0)
			dq_check = !dq_check;
		if (str[i] == QUOTE && dq_check == 0)
			sq_check = !sq_check;
		i++;
	}
	if (dq_check == 0)
		return (1);
	return (0);
}*/

//in this function we want the name/key of the variable to expand
//then when we got it, we will know which value to look for, thanks to that result
//if we find a dollar, we want to know if after it's not a '?'
//if it's not, we will store the characters until we found a character that is different from letters || _
char	*get_expansion_name(t_mini *mini, char *str)//malloc ⚠️
{
	char	*result;
	int		counter;
	int		tmp;
	int		i;

	result = NULL;
	counter = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if (i < (int)ft_strlen(str) - 1
		&& (ft_isalpha((int)str[i + 1]) == 1 || str[i + 1] == '_'))//we want to check if the next one is a letter, to be sure that is valid && not a '?'
	{
		tmp = i;
		while (str[++i] != ' ') 
			counter++;
		result = malloc(sizeof(char) * counter + 1);
		if (!result)
			print_error(mini, 2);
		i = tmp;
		tmp = 0;
		while (str[i] != ' ')
			result[tmp++] = str[i++];
		result[tmp] = '\0';
	}
	return (result);
}

char	*search_and_replace_variable(t_mini *mini, t_builtin *env_variable, char *expand_name)
{
	t_builtin	*tmp;

	tmp = env_variable;
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, expand_name) == 0)
		{
			printf("entered just before the get_value_from_env\n");
			char *result;
			result = get_value_from_env(mini, tmp->key);//malloc ⚠️
			printf("get_value_from_env = %s\n", result);
			return (result);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

//tu dois creer une fonction pour joindre les caracteres de result 
//et ceux de la valeur de l'expansion
//puis continuer a iterer la ligne/str jusqu'a la fin
//
int	calculate_malloc_size(char *str)
{
	int	to_remove;
	int	i;

	i = 0;
	to_remove = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (str[i] != ' ')
			{
				to_remove++;
				i++;
			}
		}
		i++;
	}
	return (i - to_remove);
}

//we have to check if in this str there is sth to expand
//int	check_expansion

/*char	*expand_or_not(t_mini *mini, char *str)
{
	int		simple_quote;
	int		double_quote;
	char	*result;//the string with everything written => characters and the value of the expanded variable
	char	*expansion_name;
	char	*expansion_value;
	int		i;
	int		j;

	i = 0;
	j = ;
	simple_quote = 0;
	double_quote = 0;
	if (check_all_quotes_closed(str) == 0)
		print_error(mini, 1);//not well written
	result = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(expansion_value))+ 1);//you have to calculate the right size of what we have to write
	while (str[i])
	{
		if (str[i] == DQUOTE && simple_quote == 0)
			double_quote = !double_quote;
		else if (str[i] == QUOTE && double_quote == 0)
			simple_quote = !simple_quote;
		else if (simple_quote == 1)//in this case we don't expand
			result[j] += str[i];
		else if (double_quote == 1)//we expand it
		{
			//if it's a $
			if (str[i] == '$')//you have to concatenate what we had in result + the value of the expanded variable
			//it's possible that we don't enter here because the $ has a special behavior.
			//It's not considered as a usual character but like an expansion
			{
				expansion_name = get_expansion_name(mini, str);//malloc ⚠️
				if (!expansion_name)
					//there is no characters after the '$'
				expansion_value = search_and_replace_variable(mini, mini->env, expansion_name);//malloc ⚠️
				if (!expansion_value)
					//we didn't found the varaible name in the env => it doesn't exists
				result[j] = ft_strjoin(result, expansion_value);//malloc ⚠️
				j += ft_strlen(expansion_value);
				if (!result)
					print_error(mini, 2);
			}
				//search_and_replace_variable with strjoin
				//we want to search for the variable that is the same as the name after the $
				//and join his value with what we had before
			else if (str[i] == BACKSLASH)
				i++;
			else
				result[j++] += str[i];
		}
		else
		{

		}
		i++;
	}
	return (result);
}*/

//we want a function that returns the string with the characters:
// - before the expanded value && the value of the expanded variable
//we suppose that there is a string with only 1 variable to expand
//let's say that the string in argument is everything from the beginning until the end of the expanded variable
//if there is others variables to expand, we have to recall this function starting from this index
char	*expanded_string(t_mini *mini, char *str)
{
	int		i;
	int		j;
	int		k;
	char	*result;
	char	*expanded_key;
	char	*expanded_value;

	write(1, "1\n", 2);
	i = calculate_malloc_size(str);//we calculate the size only for the character (the one that are not related to the expansion)
	expanded_key = get_expansion_name(mini, str);//to protect && to free
	if (!expanded_key)
		print_error(mini, 2);
	write(1, "2\n", 2);
	expanded_value = search_and_replace_variable(mini, mini->env, expanded_key);//to protect && to free
	if (!expanded_value)
		print_error(mini, 2);
	write(1, "3\n", 2);
	j = (int)ft_strlen(expanded_value);
	result = malloc(sizeof(char) * (i + j) + 1);
	printf("--------------------------\n");
	printf("result size = %i\n", i + j + 1);
	printf("expanded key = %s\n",  expanded_key);
	printf("expanded value = %s\n", expanded_value);
	printf("--------------------------\n");
	if (!result)
		print_error(mini, 2);
	i = 0;
	j = 0;
	k = 0;
	write(1, "4\n", 2);
	while (str[i])
	{
		if (str[i] != '$')
			result[j++] = str[i++];
		else
		{
			while (expanded_value[k])
				result[j++] = expanded_value[k++];
			i += (int)ft_strlen(expanded_key) + 1;//+ 1 for the $
		}
		write(1, "5\n", 2);
	}
	return (free(expanded_key), free(expanded_value), result);
}

//you have to do a function that returns an int
//this int means that is it or in a DQUOTE or in a simple QUOTE
//in this case we know if we have to expand or not

//we have to check if all quotes are closed to execute command with quotes
//if there is one open, we return 0. It means the command can't be executed
int	check_all_quotes_closed(char *str)
{
	int	simple_quote;
	int	double_quote;
	int	i;

	simple_quote = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
			simple_quote = !simple_quote;
		if (str[i] == DQUOTE)
			double_quote = !double_quote;
		i++;
	}
	if (simple_quote == 0 && double_quote == 0)
		return (1);
	return (0);
}
