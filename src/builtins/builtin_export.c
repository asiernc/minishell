/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/14 18:43:47 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// mirar ft_strcmp libft minishell

/*int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}*/

//I HAVE TO REMOVE THE NODE->KEY = _ BECAUSE IT ISN'T IN EXPORT
void	remove_special_node(t_builtin **head)
{
	t_builtin	*current;
	t_builtin	*previous;

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
t_builtin	*sort_ascii(t_builtin *lst_export, t_builtin *sorted)
{
	t_builtin	*current;
	t_builtin	*the_next;
	t_builtin	*tmp;

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
	int			i;
	i = 0;

	while (str[i] != '=')
	{
		if (i == 0 && str[i] == 34)
			i++;
		else if (i == 0 && str[i] != '_' && !ft_isalpha(str[i]))//si ce n'est pas un _ ou une lettre de l'alphabet
			return (perror("export: not a valid identifier"), 0);//alors cest mal ecrit
		i++;
	}
	if (i > 0 && str[i] == '=' && str[i - 1] == '+')
		return (2);//in the case for joining the values
	if (i > 0)
		return (1);//in the case for adding  new variable in the env
	return (0);
}

//lst refers to the list that contains all the lines of the export env
//in this function, str refers to the new export variable. ie: 'abc=test'
t_builtin	*add_export_variable(t_builtin *lst, char *str, char *value_trimmed)
{
	t_builtin	*new_node;
	t_builtin	*tmp;
	int			lst_size;

	tmp = lst;
	lst_size = ft_lstsize_builtin(lst);
	new_node = malloc(sizeof(t_builtin));
	if (!new_node)
		return (NULL);
	new_node->key = get_key_from_env(str);
	if (!new_node->key)
		return (free(new_node), NULL);
	new_node->value = value_trimmed;
	if (!new_node->value)
		return (free(new_node), NULL);
	new_node->index = lst_size - 1;
	new_node->next = NULL;
	ft_lstadd_back_builtin(&lst, new_node);
//	lst = sort_ascii(lst, NULL);
	return (lst);
}

void	join_values(t_builtin **lst_export, char *str)
{
	t_builtin	*tmp;
	char		*key_str;
	char		*value_str;
	char		*value_node;

	key_str = get_key_from_env(str);
	if (!key_str)
		return ;
	value_str = get_value_from_env(str);
	if (!value_str)
		return (free(key_str));
	tmp = *lst_export;
	while (ft_strcmp(tmp->key, key_str))//while it's different
		tmp = tmp->next;
	value_node = tmp->value;
	free(tmp->value);
	tmp->value = ft_strjoin(value_node, value_str);
	free(key_str);
	free(value_str);
}

//if the variable already exists and we want to change it complelty
char	*check_key_already_exists(t_builtin *lst_export, char *str)
{	
	t_builtin	*tmp;
	char		*key_str;

	tmp = lst_export;
	while (tmp)
	{
		key_str = get_key_from_env(str);
		if (!key_str)
			perror("malloc error src/builtins/builtin_export.c l.102");
		if (ft_strcmp_simple(tmp->key, key_str) == 0)
			return (key_str);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*trim_quotes(char *str)//YOU MIGHT HAVE A LEAK HERE BECAUSE YOU MALLOC WITHOUT FREE THE PREVIOUS CONTENT
{
	int		i;
	int		j;
	int		len;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	while (str[i] == 34 || str[i] == 39)
		i++;
	j = (int)ft_strlen(str) - 1;
	while (str[j] == 34 || str[j] == 39)
		j--;
	j++;
	len = j - i;
	return (ft_substr(str, i, len));
}


int	builtin_export(t_mini *mini, char **cmd)
{
	t_builtin	*lst_export;
	t_builtin	*tmp;
	char		*key_str;
	char		*value_trimmed;

	lst_export = create_builtin_lst(mini->env);
	if (!lst_export)
		perror("error creating the list for the env");
	if (cmd[1] != NULL)
	{
		//on veut egalement checker si lorsque l'on a export HOME=simon => on efface le noeud HOME pour recreer sa valeur
		//on veut checker si la valeur a exporter existe deja ou pas
		if (check_variable(cmd[1]) == 1)
		{
			key_str = check_key_already_exists(lst_export, cmd[1]);
			if (key_str)
				builtin_unset(&lst_export, key_str);	
			value_trimmed = trim_quotes(cmd[1]);
			if (!value_trimmed)
				return (0);
			printf("key_str after trim = %s\n", value_trimmed);
			lst_export = add_export_variable(lst_export, cmd[1], value_trimmed);
		}
		else if (check_variable(cmd[1]) == 2)
			join_values(&lst_export, cmd[1]);
	}
//	lst_export = sort_ascii(lst_export, NULL);
	tmp = lst_export;
	remove_special_node(&tmp);
	while (tmp)
	{
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
//	ft_lstclear_builtin(&lst_export);//this line will be written at the very last step of the pgrm. Just before return (0) of the main
	return (1);
}

/*int	main(int argc, char **argv, char **env)
{
//	builtin_export(env, "PAGER+=TEEEEEEEEEEEEEEEST");
	builtin_export(env, "PAGER+=SIIIIIIIIIIIIIIMON");
	argc = 0;
	argv[0] = "./a.out";
//	unset_builtin(env, "PAGER");
//	printf("%lu\n", sizeof(t_builtin));
//	printf("%p\n", argc);
	return (0);
}*/
