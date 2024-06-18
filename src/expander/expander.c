/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:36:34 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/18 19:58:07 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//before doing anything, we have to check if the env variable HOME is set or not
//if it's not set, we go out from our minishell because the project didn't asked
//to manage the system variables
void	check_cd_home(t_mini *mini, t_cmd *cmd)
{
	if (cmd->str && (ft_strcmp_simple(cmd->str[0], "cd") == 0)
		&& (cmd->str[1] && (ft_strcmp_simple(cmd->str[1], "~") == 0
				|| ft_strcmp_simple(cmd->str[1], "~/") == 0)))
	{
		if (variable_existence(mini, "$HOME", 0) == 0)
		{
			if (!mini->home_env)
				print_error(mini, UNSET_HOME);
		}
	}
}

//il faut creer une fonction qui check si nous sommes dans l'export ou pas
//si c'est le cas, alors il faut rajouter des comillas a chaque debut et fin
//de value
int	check_export_expansion(t_cmd *cmd)
{
	if (cmd->str && ft_strcmp_simple(cmd->str[0], "export") == 0)
		return (1);
	return (0);
}

//si on est dans l'export et que le premier caractere apres l'egal est une quote
//alors on va faire un substring de cette string
//une fois que l'on aura cette substring,

//managing export function	
/*	flag_export = check_export_expansion(cmd);
	printf("flag_export = %i\n", flag_export);
	if (flag_export == 1)
	{
		char	**array;
		int		k = 0;
		i = 0;
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
		return (array);
	}
*/
void	run_expander(t_mini *mini, t_cmd *cmd)
{
	t_lexer	*tmp;
//	int		flag_export;

/*check to see what are the inputs given
	int	i = 0;
	while (cmd->str[i])
	{
		printf("before expansion cmd->str[%i] = _%s_\n",i, cmd->str[i]);
		i++;
	}
*/
	cmd->str = expand_cmd_line(mini, cmd->str);
	check_cd_home(mini, cmd);
	//need the Manage expand function
	tmp = cmd->redirections;
	while (tmp)
	{
		if (tmp->token != HDOC)
			tmp->str = expand_str_line(mini, tmp->str);
		tmp = tmp->next;
	}
	//printf("after expansion cmd->str = _%s_\n", cmd->str[1]);
}

// expand cmd line. only cmd flags and args of the cmd
char	**expand_cmd_line(t_mini *mini, char **str)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	while (str[i])
	{
		new = final_expansion(mini, str[i]);
		free(str[i]);
		str[i] = new;
		//printf("cmd->str[%i] = _%s_\n", i, new);
		i++;
	}
	return (str);
}

// expand str==> filename
char	*expand_str_line(t_mini *mini, char *str)
{
	char	*new;

	new = NULL;
	new = final_expansion(mini, str);
	free(str);
	str = new;
	return (str);
}
