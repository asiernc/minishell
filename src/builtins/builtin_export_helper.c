/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:58:10 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/13 12:08:16 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*value_with_quotes(char *str);

void	print_env_export(t_mini *mini, int flag)//t_env_lst *lst_env, )
{
	t_env_lst	*tmp;

	tmp = mini->env;
	if (flag == 0)
	{
		while (tmp)
		{
			if (tmp->key && tmp->value)
				printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	else if (flag == 1)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->key, "_", 1) != 0)
			{
				if (tmp->value == NULL)
					printf("declare -x %s\n", tmp->key);
				else
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			}
			tmp = tmp->next;
		}
	}
}

//I HAVE TO REMOVE THE NODE->KEY = _ BECAUSE IT ISN'T IN EXPORT
void	remove_special_node(t_env_lst **head)
{
	t_env_lst	*current;
	t_env_lst	*previous;

	previous = NULL;
	current = *head;
	if (*head == NULL)
		return ;
	while (current)
	{
		if (ft_strcmp(current->key, "_") == 0)
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

//there is a second argument whereas I only need one. I had norminette issues.
//This second argument has to be set as NULL
t_env_lst	*sort_ascii(t_env_lst *lst_export, t_env_lst *sorted)
{
	t_env_lst	*current;
	t_env_lst	*the_next;
	t_env_lst	*tmp;

	current = lst_export;
	while (current)
	{
		the_next = current->next;
		if (!sorted || ft_strcmp(current->key, sorted->key) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			tmp = sorted;
			while (tmp->next && ft_strcmp(current->key, tmp->next->key) >= 0)
				tmp = tmp->next;
			current->next = tmp->next;
			tmp->next = current;
		}
		current = the_next;
	}
	return (sorted);
}

//we want to check if everything is well written before the '='.
//It means if there is a key name to the str.
//we check if it's writtent like this: for+=example || for=example
//here: str <=> 'simon=test'
int	check_variable(char *str)
{
	char	*tmp;
	int	i;
	
	i = 0;
	tmp = str;
	if (ft_strchr(tmp, '=') != NULL)
	{
		while (str[i] != '=')// || str[i])
		{
			if (i == 0 && str[i] == 34)
				i++;
			else if (i == 0 && str[i] != '_' && !ft_isalpha(str[i]))//si ce n'est pas un _ ou une lettre de l'alphabet
				return (perror("export: not a valid identifier"), 0);//alors cest mal ecrit
			i++;
		}
	}
	else
		i = 1;
	if (i > 0 && str[i] == '=' && str[i - 1] == '+')
		return (2);//in the case for joining the values
	if (i > 0)
		return (1);//in the case for adding  new variable in the env
	return (0);
}

char	*clean_value(char *str)//YOU MIGHT HAVE A LEAK HERE BECAUSE YOU MALLOC WITHOUT FREE THE PREVIOUS CONTENT
{
	int		i;

	if (ft_strchr(str, '=') == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	if (str[i] == '\0')
		return (ft_strdup(""));
	if (str[i] == 34 || str[i] == 39)
		return (value_with_quotes(&str[i]));
	else
		return (ft_strdup(&str[i]));
}

static char	*value_with_quotes(char *str)
{
	char	del;
	int		len;
	char	*res;
	int		i;
	char	*final;

	del = str[0];
	len = (int)ft_strlen(str) - 1;
	while (str[len])
	{
		if (str[len] == del)
			res = ft_substr(str, 1, len - 1);//proteger
		len--;
	}
	len = (int)ft_strlen(res);
	i = 0;
	while (res[i])
	{
		if (ft_strchr(res, del))
			len--;
		i++;
	}
	final = malloc(sizeof(char) * len + 1);
	i = 0;
	len = 0;
	while (res[i])
	{
		if (res[i] != del)
			final[len++] = res[i];
		i++;
	}
	final[len] = '\0';
	return(free(res), final);
}

