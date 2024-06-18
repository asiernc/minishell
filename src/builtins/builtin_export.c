/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/18 15:01:38 by anovio-c         ###   ########.fr       */
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

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	char		**new_cmd;
	char		*value_trimmed;
	int			i;
	//char		*str;

/*	while (cmd->str[i])
	{
		if (cmd->str[i + 1])
		{
			str = ft_strjoin(cmd->str[i], " ")
		}
	}*/
	new_cmd = ft_split(cmd->str[1], ' ');
	if (ft_strcmp(new_cmd[0], "export") == 0 && new_cmd[1] == NULL)
		print_env_export(mini, 1);
	i = 1;
	printf("NEW CMD 1 %s, %s, %s\n", new_cmd[0], new_cmd[1], new_cmd[2]);
	while (new_cmd[i])
	{
		printf("STR %s\n", new_cmd[i]);
		if (check_variable(new_cmd[i]) == 1)
		{
			check_key_already_exists(mini, mini->env, new_cmd[i]);
			value_trimmed = clean_value(mini, new_cmd[i]);
			printf("value_trimmed = _%s_\n", value_trimmed);
			mini->env = add_export_variable(mini, mini->env, new_cmd[i],
					value_trimmed);
		}
		else if (check_variable(new_cmd[i]) == 2)
			join_values(mini, &mini->env, new_cmd[i]);
		i++;
	}
	ft_free_double_array(&mini->env_cpy);
	concat_lst_env(mini);
	return (EXIT_SUCCESS);
}