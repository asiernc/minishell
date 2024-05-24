/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_part_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:23:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/24 12:08:01 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// the goal is to write the line correctly
// if we have 'this is a $TEST for $HOME $USER \$PAGE"
// the result 'this is a  for /Users/login login $PAGE"
//
//we have the function to change the $HOME with the expanded value
//we have the function to forget $TEST
//we have the function to calculate_right_malloc_size 
//we have the function to know the env variable_existence

char	*expand_the_line(t_mini *mini, char *str)
{
	int		i;
	int		j;
	int		k;
	int		len_expansion;
	char	*result;
	char	*env_key;
	char	*env_value;
	
	i = 0;
	j = 0;
	result = NULL;
	len_expansion = calculate_right_malloc_size(mini, str);
	result = malloc(sizeof(char) * len_expansion + 1);
	if (!result)
		print_error(mini, 2);
	while (str[i])
	{
		if (str[i] == BACKSLASH)
			i++;
		if ((i > 0 && str[i] == '$' && str[i - 1] == BACKSLASH) || (str[i] != '$'))//random characters*/
			result[j] = str[i];
		else
		{
			if (variable_existence(mini, str, i) == 1)
			{
				env_key = catch_expansion_key(mini, str, &i);//malloc ⚠️ //should you protect it ?
				env_value = search_and_replace_variable(mini->env, env_key);
				k = 0;
				while (env_value[k])
					result[j++] = env_value[k++];
				free(env_key);
			}
			else
				forget_the_variable(str, &i);
			result[j] = str[i];
		}
		j++;
		i++;
	}
	return (result);
}

