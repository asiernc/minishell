/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/15 14:13:57 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	value_str = trim_quotes(str);
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

int	builtin_export_1(t_builtin *lst_export)
{
	t_builtin	*tmp;

	lst_export = sort_ascii(lst_export, NULL);
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

//I had norminette issues so I had to cut this functions in two
int	builtin_export(t_mini *mini, char **cmd)
{
	t_builtin	*lst_export;
	char		*key_str;
	char		*value_trimmed;

	lst_export = create_builtin_lst(mini->env);
	if (!lst_export)
		return (perror("error creating the list for the env"), 0);
	if (cmd[1] != NULL)
	{
		if (check_variable(cmd[1]) == 1)
		{
			key_str = check_key_already_exists(lst_export, cmd[1]);
			if (key_str)
				builtin_unset(&lst_export, key_str);
			value_trimmed = trim_quotes(cmd[1]);
			if (!value_trimmed)
				return (0);
			lst_export = add_export_variable(lst_export, cmd[1], value_trimmed);
		}
		else if (check_variable(cmd[1]) == 2)
			join_values(&lst_export, cmd[1]);
	}
	return (builtin_export_1(lst_export));
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
