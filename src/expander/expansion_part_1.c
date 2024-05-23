/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_part_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:38:12 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/23 18:14:25 by simarcha         ###   ########.fr       */
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
			if (variable_existence(mini, str, i) == 1)
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

char	*catch_expansion_key(t_mini *mini, char *str, int *i)//malloc ⚠️  
{
	char	*result;
	int		counter;
	int		tmp;

	printf("------IN CATCH_EXPANSION_KEY------\n");
	result = NULL;
	counter = 0;
	printf("i memory adress = %p\ncatch_expansion_key, i = %i\n", &i, *i); 
	(*i)++;//to forget the $ && to go on 
	printf("i memory adress = %p\ncatch_expansion_key, i = %i\n", &i, *i); 
	tmp = *i;
	while (str[*i] && str[(*i)++] != ' ')
	{
		printf("i memory adress = %p\ncatch_expansion_key, i = %i\n", &i, *i); 
		counter++;
	}
	result = malloc(sizeof(char) * counter + 1);
	if (!result)
		print_error(mini, 2);
	printf("after malloc i memory adress = %p\ncatch_expansion_key, i = %i\n", &i, *i); 
	*i = tmp;
	tmp = 0;
	printf("i memory adress = %p\ncatch_expansion_key, i = %i\n", &i, *i); 
	while (str[*i] && str[*i] != ' ')
	{
		printf("i memory adress = %p\ncatch_expansion_key, i = %i\n", &i, *i); 
		result[tmp++] = str[(*i)++];
	}
	result[tmp] = '\0';
	printf("i memory adress = %p\ncatch_expansion_key, i = %i\n", &i, *i); 
	printf("------OUT CATCH_EXPANSION_KEY------\n");
	return (result);
}

// if we have "this is a $TEST for $HOME $USER \$PAGE"
// the result "this is a  for /Users/login login $PAGE"
// this function has to return: 39
//
int	calculate_right_malloc_size(t_mini *mini, char *str)
{
	int			i;
	int			counter;
	char		*env_key;
	char		*env_value;
	int			check;
	
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
				write(1, "entered in if\n", 14);
				env_key = catch_expansion_key(mini, str, &i);//malloc ⚠️  
				printf("i memory adress = %p\nafter catch_expansion_key, i = %i\n", &i, i); 
				printf("env_key memory adress = %p-----\nenv_key: %s\n", &env_key, env_key);
				env_value = search_and_replace_variable(mini->env, env_key);
				printf("env_value: %s\n", env_value);
				counter += ft_strlen(env_value);
				printf("counter = %i\n", counter);
				free(env_key);
				check++;
				if (check > 1)
					counter++;
			}
			else
				forget_the_variable(str, &i);
		}
		i++;
		printf("counter = %i\n", counter);
	}
	return (counter);
}
