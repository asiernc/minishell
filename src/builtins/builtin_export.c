/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:29:34 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/13 12:27:00 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//static char	**clear_line_export(char **str);
//lst refers to the list that contains all the lines of the export env
//in this function, str refers to the new export variable. ie: 'abc=test'
static t_env_lst	*add_export_variable(t_mini *mini, t_env_lst *lst, char *str, char *value_trimmed)
{
	static int	index = 10000;
	t_env_lst	*new_node;

	new_node = malloc(sizeof(t_env_lst));
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
//	lst = sort_ascii(lst, NULL);
	return (lst);
}

static void	join_values(t_mini *mini, t_env_lst **lst_export, char *str)
{
	t_env_lst	*tmp;
	char		*key_str;
	char		*value_str;
	char		*value_node;

	key_str = get_key_from_env(mini, str);
	if (!key_str)
		return ;
	value_str = get_value_from_env(mini, str);
	printf("VALUE STR %s\n", value_str);
	value_str = clean_value(str);
	if (!value_str)
		print_error(mini, 2);
	tmp = *lst_export;
	while (ft_strcmp(tmp->key, key_str))//while it's different
		tmp = tmp->next;
	value_node = ft_strdup(tmp->value);
	//printf("VALUE node %s\n", value_node);
	free(tmp->value);
	tmp->value = ft_strjoin(value_node, value_str);
	free(key_str);
	free(value_str);
}

//if the variable already exists and we want to change it complelty
static void	check_key_already_exists(t_mini *mini, t_env_lst *lst_export, char *str)
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
			delone_node_env(tmp->index, &lst_export);
		tmp = tmp->next;
	}
}

int	builtin_export(t_mini *mini, t_cmd *cmd)
{
	//t_env_lst	*lst_export;
	//char		**line;
	char		*value_trimmed;
	int			i;
	
	if (ft_strcmp(cmd->str[0], "export") == 0 && cmd->str[1] == NULL)
		print_env_export(mini, 1);
	printf("CLean 1 %s\n", cmd->str[1]);
	//line = clear_line_export(cmd->str);
	//printf("CLean 2 %s\n", line[1]);
	i = 1;
	while (cmd->str[i])
	{
		if (check_variable(cmd->str[i]) == 1)
		{
			check_key_already_exists(mini, mini->env, cmd->str[i]);
			value_trimmed = clean_value(cmd->str[i]);
			mini->env = add_export_variable(mini, mini->env, cmd->str[i], value_trimmed);
		}
		else if (check_variable(cmd->str[i]) == 2)
			join_values(mini, &mini->env, cmd->str[i]);
		i++;
	}
	//free(value_trimmed);//?????
	//ft_free_double_array(mini->env_cpy);
	concat_lst_env(mini);
	return (EXIT_SUCCESS);
}

/*static char	**clear_line_export(char **str)
{
	int		i;
	char	**result;
	char	*tmp;
	char	*previous;

	i = 0;
	while (str[i])
	{
		fprintf(stderr, "STR %s \n", str[i]);
		tmp = ft_strtrim(str[i], " ");
		fprintf(stderr, "AFTER STR %s \n", str[i]);
		previous = ft_strjoin(tmp, " ");
		//free(tmp);
		i++;
	}
	result = ft_split(previous, ' ');
	//fprintf(stderr, "TRIMMED2 %s // %s\n", result[0], result[1]);
	return (result);
}*/


/*static char **clear_line_export(char **str)
{
    int		i;
    char	*result_str = NULL;
    char	*tmp;
    char	*trimmed;
	char	**result;

	i = 0;
    while (str[i])
	{
        trimmed = ft_strtrim(str[i], " ");
        if (result_str == NULL)
            result_str = ft_strdup(trimmed);
		else
		{
            tmp = ft_strjoin(result_str, " ");
            free(result_str);
            result_str = ft_strjoin(tmp, trimmed);
            free(tmp);
        }
        free(trimmed);
        i++;
    }
	result = ft_split(result_str, ' ');
    free(result_str);
    return (result);
}*/
