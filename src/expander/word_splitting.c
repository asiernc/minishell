/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:38:51 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/31 10:32:31 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_lines_in_array(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i]) 
	{
		j = 0;
		while (array[i][j])
			j++;
		i++;
	}
	return (i);
}

char	**search_and_replace_variable_lead_zero(t_mini *mini, t_builtin *env_variable, char *expand_name)
{
	t_builtin	*tmp;
	char		**word_splitted;

	tmp = env_variable;
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, expand_name) == 0)
		{
			word_splitted = ft_split(tmp->value, ' ');
			if (!word_splitted)
				print_error(mini, 2);
			return (word_splitted);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	expand_dollar_variable_lead_zero(t_mini *mini, char *str, int *i, char *result)
{
	int		j;
	int		k;
	int		l;
	char	*env_key;
	char	**env_value;

	j = 0;
	k = 0;
	if (variable_existence(mini, str, *i) == 1)
	{
		env_key = catch_expansion_key(mini, str, i);
		if (!env_key)
			print_error(mini, 2);
		env_value = search_and_replace_variable_lead_zero(mini, mini->env, env_key);
		while (env_value[k])
		{
			l = 0;
			while (env_value[k][l])
				result[j++] = env_value[k][l++];
			if (k + 1 < count_lines_in_array(env_value))//each we call this function because I reach the limit of the possible variables declared
				result[j++] = ' ';
			k++;
		}
		free(env_key);
	}
	else
		forget_the_variable(str, i);
	result[j] = str[*i];
	return (j);
}

//this will expand the line when lead == 0.
//It means that we have to split the word by one space if there is various
//spaces in the same env
char	*expand_the_line_lead_zero(t_mini *mini, char *str)//malloc ⚠️  
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	result = NULL;
	j = calculate_len_for_malloc(mini, str);//you're allocating too much space for word splitting //you should create a function calculate_len_for_malloc_lead_zero
	result = malloc(sizeof(char) * j + 1);
	if (!result)
		print_error(mini, 2);
	j = 0;
	while (str[i])
	{
		if (str[i] == BACKSLASH)
			i++;
		if ((i > 0 && str[i] == '$' && str[i - 1] == BACKSLASH)
			|| (str[i] != '$'))
			result[j++] = str[i++];
		else
			j += expand_dollar_variable_lead_zero(mini, str, &i, &result[j]);
	}
	result[j] = '\0';
	return (result);
}
