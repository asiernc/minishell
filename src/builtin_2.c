/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:11:30 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/29 19:13:57 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct	store_env
{
	char				*key;//the name of the variable in env
	char				*value;
	struct store_env	*next;
}				t_env;

//for each line of our env, we want to get the characters before the '='
//this will be the content of the 'key' variable in our structure
char	*get_key_from_env(char *str)//to free once used
{
	int		i;
	int		len_str;
	char	*result;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	len_str = i;
	result = malloc((len_str + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len_str)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

//for each line of our env, we want to get the characters after the '='
//this will be the content of the 'value' variable in our structure
char	*get_value_from_env(char *str)
{
	int		i;
	int		j;
	int		len_str;
	char	*result;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	i++;
	j = i;
	while (str[i])
		i++;
	len_str = i - j;
	result = malloc((len_str + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (j < (int)ft_strlen(str))
		result[i++] = str[j++];
	result[j] = '\0';
	return (result);
}

t_env	*ft_lstnew_env(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = get_key_from_env(str);
	if (!node->key)
		return (free(node), NULL);
	node->value = get_value_from_env(str);
	if (!node->value)
		return (free(node), NULL);
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

//to test
void	print_list(t_env **lst_env)
{
	int	i;

	i = 1;
	printf("list memory adress [%p]\n", lst_env);
	while (*lst_env)
	{
		printf("--------node%i--------\n", i);
		printf("memory adress [%p]\n", *lst_env);
		printf("key: %s\n", (*lst_env)->key);
		printf("value: %s\n", (*lst_env)->value);
		i++;
		*lst_env = (*lst_env)->next;
	}
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
	lst = NULL;
}

t_env	*init_env_node(char **env)
{
	t_env	*new_node;
	t_env	*lst_env;
	int		i;

	i = 0;
	lst_env = NULL;
	while (env[i])
	{
		new_node = ft_lstnew_env(env[i]);
		if (!new_node)
			return (NULL);
		ft_lstadd_back_env(&lst_env, new_node);
		i++;
	}
	return (lst_env);
}

void	builtin_env(char **env)
{
	t_env	*lst_env;
	t_env	*tmp;

	lst_env = init_env_node(env);
	if (!lst_env)
		perror("error creating the list for the env");
	tmp = lst_env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	ft_lstclear_env(&lst_env);
}

int	main(int argc, char **argv, char **env)
{
//	init_env_node(env);
/*	char	str[99] = "TERM_SESSION_ID=w0t0p0:FA308702-45DC-4F06-9BFA-6376AC07D0A8";
	printf("ft_strlen(env[0]) = %zu\n", ft_strlen(str));
	printf("%s\n", get_key_from_env(env[29]));
	printf("%s\n", get_value_from_env(env[29]));
*/	builtin_env(env);
	argc = 0;
	argv[0] = "./a.out";
//	printf("%lu\n", sizeof(t_env));
	return (0);
}
