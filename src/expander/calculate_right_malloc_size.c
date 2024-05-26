/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_right_malloc_size.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:17:51 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/26 18:44:06 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// the goal is to write the line correctly
// if we have "this is a $TEST for $HOME $USER \$PAGE"
// the result "this is a  for /Users/login login $PAGE"
//
//we have the function to change the $HOME with the expanded value
//we have to forget $TEST
//function to forget $TEST that means, if the env variable doesn't exists

//this functions checks only for 1 variable
//this function checks if the variable that we sent is in our env
//it returns 1 if the variable is in the env
//0 if it doesn't exists
//for example if we have the command line: "$test"
//$test is not in env => it returns 0
//the argument i is important because it's where we start
int	variable_existence(t_mini *mini, char *str, int i)
{
	t_builtin	*tmp;
	int			k;
	int			j;
	char		*env_key;

//	printf("in VARIABLE_EXISTENCE i memory address = %p---\ni = %i\n", &i, i);
	i++;//to forget the '$'
	k = i;
	j = 0;
	while (str[i] && str[i++] != ' ')
		j++;
	env_key = malloc(sizeof(char) * j + 1);
	if (!env_key)
		print_error(mini, 2);
	i = k;//you can eventually remove it
	j = 0;
	while (str[i] && str[i] != ' ')
		env_key[j++] = str[i++];
	tmp = mini->env;
	while (tmp)
	{
		if (ft_strcmp_simple(env_key, tmp->key) == 0) 
			return (free(env_key), 1);
		tmp = tmp->next;
	}
	return (free(env_key), 0);
}

void	forget_the_variable(char *str, int *i)
{
//	printf("in FORGET THE VARIABLE i memory address = %p---\ni = %i\n", &i, *i);
	while (str[*i] && str[*i] != ' ')
		(*i)++;
}

//this function returns the name of the key in our env list
char	*catch_expansion_key(t_mini *mini, char *str, int *i)//malloc ⚠️  
{
	char	*result;
	int		counter;
	int		tmp;

	result = NULL;
	counter = 0;
//	printf("in the beginning of CATCH EXPANSION KEY i memory address = %p---\ni = %i\n", i, *i);
	(*i)++;//to forget the $ && to go on 
	tmp = *i;
	while (str[*i] && str[(*i)++] != ' ')//to change because the space is not the limiter
		counter++;
	result = malloc(sizeof(char) * counter + 1);
	if (!result)
		print_error(mini, 2);
	*i = tmp;
	tmp = 0;
	while (str[*i] && str[*i] != ' ')
		result[tmp++] = str[(*i)++];
	result[tmp] = '\0';
//	printf("at the end of CATCH EXPANSION KEY i memory address = %p---\ni = %i\n", i, *i);
	return (result);
}

/*int	add_value_size(t_mini *mini, int *i, int *counter, int *check)
{
	char	*env_value;

	env_value = search_and_replace_variable(mini->env, env_key);
	*counter += ft_strlen(env_value);
	(*check)++;
	if (*check > 1)
		(*counter)++;
}

// if we have "this is a $TEST for $HOME $USER \$PAGE"
// the result "this is a  for /Users/login login $PAGE"
// this function has to return: 39
//
int	calculate_right_malloc_size(t_mini *mini, char *str)
{
	int		i;
	int		counter;
	int		check;
	char	*env_key;
	
	i = 0;
	counter = 0;
	check = 0;
	printf("len str = %i\n", (int)ft_strlen(str));
	while (str[i] && i < (int)ft_strlen(str))//ca c'est moche
	{
		if (str[i] == BACKSLASH)
			i++;
		printf("i memory adress = %p-----\nstr[i] = %c\ni = %i\n", &i, str[i], i);
		if ((i > 0 && str[i] == '$' && str[i - 1] == BACKSLASH) || (str[i] != '$'))//random characters
			counter++;
		else
		{
			if (variable_existence(mini, str, i) == 1)
			{
				env_key = catch_expansion_key(mini, str, &i);//malloc ⚠️  
				add_value_size(mini, &i, &counter, &check);
				free(env_key);
			}
			else
				forget_the_variable(str, &i);
		}
		i++;
		printf("counter = %i\n", counter);
	}
	return (counter);
}*/

void	manage_dollar_variable(t_mini *mini, char *str, int *i, int *counter)
{
	char		*env_key;
	char		*env_value;

	if (variable_existence(mini, str, *i) == 1)
	{
//		write(1, "entered in if\n", 14);
//		printf("BEFORE CATCH EXPANSION KEY = %p---\ni = %i\n", i, *i);
		env_key = catch_expansion_key(mini, str, i);//malloc ⚠️  //should you protect it
//		printf("i after catch_expansion_key memory address = %p---\ni = %i\n", i, *i);
		env_value = search_and_replace_variable(mini->env, env_key);
		(*counter) += ft_strlen(env_value);
		free(env_key);
	}
	else
	{
		forget_the_variable(str, i);
//		printf("i after forget_the_variable memory address = %p---\ni = %i\n", i, *i);
	}
}

//if we have the line to expand, this function returns the size that we will
//need for the malloc
int	calculate_right_malloc_size(t_mini *mini, char *str)
{
	int			i;
	int			counter;
	int			check;

	i = 0;
	counter = 0;
	check = 0;
	while (str[i] && i < (int)ft_strlen(str))//ca c'est moche
	{
		if (str[i] == BACKSLASH)
			i++;
		if ((i > 0 && str[i] == '$' && str[i - 1] == BACKSLASH) || (str[i] != '$'))//random characters
			counter++;
		else
		{
//		printf("i before manage_dollar_variable memory address = %p---\ni = %i\n", &i, i);
			manage_dollar_variable(mini, str, &i, &counter);
/*			if (variable_existence(mini, str, i) == 1)
			{
				env_key = catch_expansion_key(mini, str, &i);//malloc ⚠️  //should you protect it
				env_value = search_and_replace_variable(mini->env, env_key);
				counter += ft_strlen(env_value);
				free(env_key);
			}
			else
				forget_the_variable(str, &i);*/
			check++;
			if (check > 1)
				counter++;
		}
		i++;
	}
	return (counter);
}

/*int	calculate_right_malloc_size(t_mini *mini, char *str)
{
	int			i;
	int			counter;
	char		*env_key;
	char		*env_value;
	int			check;

	i = 0;
	counter = 0;
	check = 0;
	while (str[i] && i < (int)ft_strlen(str))//ca c'est moche
	{
		if (str[i] == BACKSLASH)
			i++;
		if ((i > 0 && str[i] == '$' && str[i - 1] == BACKSLASH) || (str[i] != '$'))//random characters
			counter++;
		else
		{
			if (variable_existence(mini, str, i) == 1)
			{
				env_key = catch_expansion_key(mini, str, &i);//malloc ⚠️
				env_value = search_and_replace_variable(mini->env, env_key);
				counter += ft_strlen(env_value);
				free(env_key);
				check++;
				if (check > 1)
					counter++;
			}
			else
				forget_the_variable(str, &i);
		}
		i++;
	}
	return (counter);
}*/
