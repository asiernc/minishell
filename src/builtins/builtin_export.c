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
static t_builtin	*add_export_variable(t_mini *mini, t_builtin *lst, char *str, char *value_trimmed)
{
	static int	index = 10000;
	t_builtin	*new_node;
	t_builtin	*tmp;
	int			lst_size;

	tmp = lst;
	lst_size = ft_lstsize_builtin(lst);
	new_node = malloc(sizeof(t_builtin));
	if (!new_node)
		print_error(mini, 2);
	new_node->key = get_key_from_env(mini, str);
	if (!new_node->key)
		print_error(mini, 2);
	new_node->value = value_trimmed;
	/*if (!new_node->value)
	{
		fprintf(stderr, "INSIDE\n");
		print_error(mini, 2);
	}*/
	new_node->index = index++;
	new_node->next = NULL;
	ft_lstadd_back_builtin(&lst, new_node);
//	lst = sort_ascii(lst, NULL);
	return (lst);
}

static void	join_values(t_mini *mini, t_builtin **lst_export, char *str)
{
	t_builtin	*tmp;
	char		*key_str;
	char		*value_str;
	char		*value_node;

	key_str = get_key_from_env(mini, str);
	if (!key_str)
		return ;
	value_str = get_value_from_env(mini, str);
	value_str = trim_quotes(str);
	if (!value_str)
		print_error(mini, 2);
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
static void	check_key_already_exists(t_mini *mini, t_builtin *lst_export, char *str)
{
	t_builtin	*tmp;
	char		*key_str;

	tmp = lst_export;
	while (tmp)
	{
		key_str = get_key_from_env(mini, str);
		if (!key_str)
			print_error(mini, 2);
		if (ft_strcmp_simple(tmp->key, key_str) == 0)
		// free value
		{
			fprintf(stderr, "index %d\n", tmp->index);
			delone_node_env(tmp->index, &lst_export);
		}
		tmp = tmp->next;
	}
}

//I had norminette issues so I had to cut this functions in two
/*int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	t_builtin	*lst_export;
	char		*key_str;
	char		*value_trimmed;

//create_builtin_lst(mini, mini->env_cpy);
	lst_export = mini->env;
	if (!lst_export)
		print_error(mini, 2);
	if (ft_strcmp(cmd->str[0], "export") == 0 && cmd->str[1] == NULL)
		print_env_export(mini, mini->env_cpy, 1);
	if (cmd->str[1] != NULL)
	{
		if (check_variable(cmd->str[1]) == 1)
		{
			key_str = check_key_already_exists(mini, lst_export, cmd->str[1]);
			if (key_str)
				builtin_unset(mini, &mini->env, cmd);
				//builtin_unset(mini, cmd);
			value_trimmed = trim_quotes(cmd->str[1]);
			if (!value_trimmed)
				return (0);
			lst_export = add_export_variable(mini, lst_export, cmd->str[1], value_trimmed);
		}
		else if (check_variable(cmd->str[1]) == 2)
			join_values(mini, &lst_export, cmd->str[1]);
	}
	concat_lst_env(mini);
	return (EXIT_SUCCESS);
}*/

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	t_builtin	*lst_export;
	//char		*key_str;
	char		*value_trimmed;
	int			i;
	
	lst_export = mini->env;
	if (!lst_export)
		print_error(mini, 2);
	if (ft_strcmp(cmd->str[0], "export") == 0 && cmd->str[1] == NULL)
		print_env_export(mini, mini->env_cpy, 1);
	i = 1;
	while (cmd->str[i] != NULL)
	{
		if (check_variable(cmd->str[i]) == 1)
		{
			check_key_already_exists(mini, lst_export, cmd->str[i]);
			//if (key_str)
			//	builtin_unset(mini, &mini->env, cmd);
				//builtin_unset(mini, cmd);
			value_trimmed = trim_quotes(cmd->str[i]);
			//if (ft_strlen(value_trimmed) == 0)
			//	value_trimmed = NULL;
			fprintf(stderr, "TRIMED VALUE: %s\n", value_trimmed);
			//if (!value_trimmed)
			//	return (0);
			lst_export = add_export_variable(mini, lst_export, cmd->str[i], value_trimmed);
		}
		else if (check_variable(cmd->str[i]) == 2)
			join_values(mini, &lst_export, cmd->str[i]);
		i++;
	}
	concat_lst_env(mini);
	return (EXIT_SUCCESS);
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
