/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/18 19:57:15 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static char	**clear_line_export(char **str);
//lst refers to the list that contains all the lines of the export env
//in this function, str refers to the new export variable. ie: 'abc=test'
static t_env_lst	*add_export_variable(t_mini *mini, t_env_lst *lst,
				char *str, char *value_trimmed)
{
	static int	index = 150;
	t_env_lst	*new_node;

	new_node = (t_env_lst *)malloc(sizeof(t_env_lst));
	if (!new_node)
		print_error(mini, 2);
	new_node->key = get_key_from_env(mini, str);
	if (!new_node->key)
		print_error(mini, 2);
	if (value_trimmed)
		new_node->value = value_trimmed;
	else
		new_node->value = NULL;
	new_node->index = index++;
	new_node->next = NULL;
	ft_lstadd_back_builtin(&lst, new_node);
	return (lst);
}

static void	join_values(t_mini *mini, t_env_lst **lst_export, char *str)
{
	t_env_lst	*tmp;
	char		*key_str;
	char		*value_str;
	char		*value_node;
	char		*tmp_join;

	key_str = get_key_from_env(mini, str);
	//printf("key_str= _%s_\n", key_str);
	if (!key_str)
		return ;
	value_str = clean_value(mini, str);
	printf("value_str = _%s_\n", value_str);
	if (!value_str)
	{
		free(key_str);
		print_error(mini, 2);
	}
	tmp = *lst_export;
	while (tmp)
	{
		//printf("entered in while\n");
		if (!ft_strcmp(tmp->key, key_str))
		{
			//printf("tmp->key= _%s_\n", tmp->key);
			//printf("entered in strcmp\n");
			value_node = ft_strdup(tmp->value);
			free(tmp->value);
			tmp->value = ft_strjoin(value_node, value_str);
			free(key_str);
			free(value_str);
			free(value_node);
			return ;
		}
		tmp = tmp->next;
	}
	//printf("en dehors du while key_str= _%s_\n", key_str);
	tmp_join = ft_strjoin(key_str, "=");
	//printf("tmp_join = _%s_\n", tmp_join);
	free(key_str);
	key_str = ft_strjoin(tmp_join, value_str);
	//printf("key_str = _%s_\n", key_str);
	tmp = ft_lstnew_builtin(mini, key_str);
	ft_lstadd_back_builtin(lst_export, tmp);
	free(tmp_join);
	return (free(key_str), free(value_str));
}

//if the variable already exists and we want to change it complelty
static void	check_key_already_exists(t_mini *mini, t_env_lst *lst_export,
					char *str)
{
	t_env_lst	*tmp;
	char		*key_str;

	tmp = lst_export;
	key_str = get_key_from_env(mini, str);
	if (!key_str)
		print_error(mini, 2);
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, key_str) == 0)
		{
			delone_node_env(tmp->index, &lst_export);
			break ;
		}
		tmp = tmp->next;
	}
	free(key_str);
}

//on veut creer une fonction qui check si apres l'egal il y a une QUOTE || DQUOTE
/*int	check_quote_after_equal(char *str)
{
	int	i;

	if (ft_strchr(str, '=') == NULL)
		return (-1);
	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	if (str[i] == QUOTE || str[i] == DQUOTE)
		return (1);
	return (0);
}*/

//le but est de retourner un array de string qui contient toutes les variables a expandre
//par exemple: 			str  : var1="this  is a test " var2="for export" var3=ok
//the result has to be: array: [[var1="this  is a test "], [var2="for export"], [var3=ok], [NULL]]
/*char	**array_of_variables_to_expand(t_mini *mini, char *str)
{
	int		i;
	char	**array;
	int		k;

	i = 0;
	k = ;
	array = malloc(sizeof(char) * k + 1);
	if (!array)
		print_error(mini, 2);
	k = 0;
	while (str[i])
	{
		array[k] = get_key_from_env(mini, str);//proteger et free
		k++;
		while (str[i])
		{
			if (str[i] == '=')
				break ;
			i++;
		}
		if (str[i] == QUOTE || str[i] == DQUOTE)
		{
			array[k] = value_in_quotes(mini, str, i);
			k++;
		}
		i++;
	}
	array[k] = NULL;
	return (array);
}*/

/*
	while (cmd->str[i])//check to see if there is quote or not => if theere is not, wee don't have to split it because it's well done by default
	{
		while (cmd->str[i][j])
		{
			if (cmd->str[i][j] == QUOTE || DQUOTE)
				check = 1;
			j++;
		}
		i++;
	}
	if (check == 0)
}*/

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	//char		**cmd->str;
	char		*value_trimmed;
	int			i;

	if (ft_strcmp(cmd->str[0], "export") == 0 && cmd->str[1] == NULL)
		print_env_export(mini, 1);
	i = 1;
	while (cmd->str[i])
	{
		printf("cmd->str = _%s_\n", cmd->str[i]);
		if (check_variable(cmd->str[i]) == 1)
		{
			check_key_already_exists(mini, mini->env, cmd->str[i]);
			value_trimmed = get_value_from_env(mini, cmd->str[i]);//I changed it a bit
			//value_trimmed = clean_value(mini, cmd->str[i]);
			printf("value_trimmed = _%s_\n", value_trimmed);
			mini->env = add_export_variable(mini, mini->env, cmd->str[i],
					value_trimmed);
		}
		else if (check_variable(cmd->str[i]) == 2)
			join_values(mini, &mini->env, cmd->str[i]);
		i++;
	}
	ft_free_double_array(&mini->env_cpy);
	concat_lst_env(mini);
	return (EXIT_SUCCESS);
}