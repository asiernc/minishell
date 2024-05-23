/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_part_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:38:12 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/23 14:45:49 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// the goal is to write the line correctly
// if we have 'this is a $TEST for $HOME $USER \$PAGE"
// the result 'this is a  for /Users/login login $PAGE"
//
//we have the function to change the $HOME with the expanded value
//we have to forget $TEST
//function to forget $TEST that means, if the env variable doesn't exists

//function that returns 1 if the variable exists, 0 otherwise

void	send_line(t_mini *mini, char *str)
{
	int		i;
	char	*expanded_value;

	i = 0;
	while (str[i])
	{
		if (str[i] == BACKSLASH)
			i++;
		if ((i > 0 && str[i] == '$' && str[i - 1] == BACKSLASH) || (str[i] != '$'))
		{
			if (write(1, &str[i], 1) == -1)
				print_error(mini, 12);
		}
		else
		{
			if (variable_existence(mini, str, &i) == 1)
			{
				expanded_value = expanded_string(mini, str); //malloc ⚠️  
				if (write(1, expanded_value, ft_strlen(expanded_value)) == -1)
					print_error(mini, 12);
				free(expanded_value);
			}
			else 
				continue ;
		}
		i++;
	}
//	if (write(1, "\n", 1) == -1)
//		print_error(mini, 12);
}

//this functions checks only for 1 variable
//there is no while loop
//this function checks if the variable that we sent is our env
//it returns 1 if the variable is in the env
//0 otherwise
//for example if we have the command line: this is a $test
//$test is not in env => it returns 0
//you have to use this fonction starting from the $ character
int	variable_existence(t_mini *mini, char *str, int i)
{
	t_builtin	*tmp;
	int			k;
	int			j;
	char		*env_key;

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

static void	forget_the_variable(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ')
		(*i)++;
}

char	*catch_expansion_key(t_mini, char *str, int *i)//malloc ⚠️  
{
	char	*result;
	int		counter;
	int		tmp;

	result = NULL;
	counter = 0;
	while (str[*i] && str[*i] != ' ')
	{
		tmp = *i;
		while (str[++(*i)] != ' ')//to forget the $ && to go on 
			counter++;
		result = malloc(sizeof(char) * counter + 1);
		if (!result)
			print_error(mini, 2);
		*i = tmp;
		tmp = 0;
		while (str[*i] != ' ')
			result[tmp++] = str[(*i)++];
		result[tmp] = '\0';
	}
	return (result);
}

// if we have 'this is a $TEST for $HOME $USER \$PAGE"
// the result 'this is a  for /Users/login login $PAGE"
// this function has to return: 39
int	calculate_right_size_malloc(t_mini, char *str)
{
	int			i;
	int			counter;
	char		*env_key;
	char		*env_value;
	t_builtin	*tmp;
	
	i = 0;
	counter = 0;
	if (str[i] == BACKSLASH)
		i++;
	if ((i > 0 && str[i] == '$' && str[i - 1] == BACKSLASH) || (str[i] != '$'))//random characters
	{
		counter++;
		i++;
	}
	else
	{
		if (variable_existence(mini, mini->line, i) == 1)//malloc ⚠️  
		{
			env_key = catch_expansion_key(mini, str, &i);
			tmp = mini->env;			
			while (tmp)
			{

				tmp = tmp->next;
			}
			//we will stock the name of the variable
			//and add the len of the value to the counter
		}
		else
			forget_the_variable(str, &i);

	}
	
}
