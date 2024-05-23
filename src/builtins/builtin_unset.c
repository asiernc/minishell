/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:25:52 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/14 13:04:40 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//**head refers to the env builtin list
//the str refers to the unset_arg to remove (for example PWD)
//this function is basically remove a node

int	scan_start_unset_arg(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->str[1] || cmd->str[1][0] == '_'
		|| (cmd->str[1][0] == '\'' && cmd->str[1][1] == '\0'))
		return (EXIT_SUCCESS);
	while (cmd->str[1][i])
		i++;
	i--;
	if (cmd->str[1][i] == '/' || cmd->str[1][i] == '\\')
	{
		ft_putstr_fd("shelldone: unset: `", STDERR_FILENO);
		ft_putstr_fd(&cmd->str[1][i], STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

int	detect_unset_error(t_cmd *cmd)
{
	char	*unset_arg;
	int		i;

	i = 0;
	unset_arg = cmd->str[1];
	if (is_equal(&unset_arg[0]) != 0)
	{
		ft_putendl_fd("shelldone: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (unset_arg[i++])
	{
		if (unset_arg[i++] == '/')
		{
			ft_putstr_fd("shelldone: unset: `", STDERR_FILENO);
			ft_putstr_fd(&unset_arg[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_mini *mini, t_builtin **head, t_cmd *cmd)
{
	char		*unset_arg;
	t_builtin	*current;
	t_builtin	*previous;

	if (mini)
		fprintf(stderr, "");
	if (scan_start_unset_arg(cmd) == 0)
		return (EXIT_SUCCESS);
	if (detect_unset_error(cmd) == 1)
		return (EXIT_FAILURE);
	unset_arg = cmd->str[1];
	previous = NULL;
	current = *head;
	while (current)
	{
		if (ft_strlen(current->key) == ft_strlen(unset_arg) &&
			ft_strcmp_simple(current->key, unset_arg) == 0)
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
	concat_lst_env(mini);
	return (EXIT_SUCCESS);
}