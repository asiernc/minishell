/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_part_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:38:12 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/23 11:16:35 by simarcha         ###   ########.fr       */
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

/*char	*send_line(t_mini *mini, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (line[i] == BACKSLASH)
			i++;
		if ((i > 0 && line[i] == '$' && line[i - 1] == BACKSLASH) || (line[i] != '$'))
			if (write(1, line[i], 1) == -1);
				print_error(mini, 12);
		else
		{
			if (variable_existence(str, &i) == 1)
				//tu gardes la value dans une variable et tu l'ecris
		}
		i++;
	}
}*/

int	variable_existence(t_mini *mini, char *str, int *i)
{
	t_builtin	*tmp;
	int			k;
	int			j;
	char		*env_key;

	write(1, "entered\n", 8);
	(*i)++;//to forget the '$'
//	printf("entered in the else\n");
	printf("i memory address : %p\nvalue i = %i\n", &i, *i);
	k = *i;
	printf("i memory address : %p\nvalue i = %i\n", &i, *i);
	printf("k memory address : %p\nvalue k = %i\n", &k, k);
	j = 0;
//	printf("before moving i, i = %i\n", i);
	while (str[*i] && str[(*i)++] != ' ')
		j++;
	printf("before the malloc: j = %i\n", j); 
	env_key = malloc(sizeof(char) * j + 1);
	if (!env_key)
		print_error(mini, 2);
	*i = k;//tu peux l'enlever
	j = 0;
	while (str[*i] && str[*i] != ' ')
		env_key[j++] = str[(*i)++];
	printf("env_key = %s\n", env_key);
	tmp = mini->env;
	while (tmp)
	{
		if (ft_strcmp_simple(env_key, tmp->key) == 0) 
		{
			printf("tmp->key = %s\n", tmp->key);
			return (free(env_key), 1);
		}
		tmp = tmp->next;
	}
	return (free(env_key), 0);
}
