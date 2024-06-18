/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:32:12 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/18 11:53:43 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_list_env(t_mini *mini)
{
	t_env_lst	*tmp_env;

	tmp_env = mini->env;
	while (tmp_env)
	{
		if (ft_strcmp_simple(tmp_env->key, "PWD") == 0)
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(mini->pwd);
		}
		if (ft_strcmp_simple(tmp_env->key, "OLDPWD") == 0)
		{
			free(tmp_env->value);
			tmp_env->value = ft_strdup(mini->old_pwd);
		}
		tmp_env = tmp_env->next;
	}
}

static void	update_path(t_mini *mini)
{
	char	*buffer;

	buffer = NULL;
	if (mini->old_pwd)
		free(mini->old_pwd);
	mini->old_pwd = ft_strdup(mini->pwd);
	buffer = getcwd(NULL, 0);
	if (mini->pwd)
		free(mini->pwd);
	mini->pwd = ft_strdup(buffer);
	free(buffer);
}

static	char	*return_value(t_mini *mini, char *str)
{
	t_env_lst	*tmp;

	tmp = mini->env;
	while (tmp)
	{
		if (ft_strcmp_simple(tmp->key, str) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

static int	do_cd(t_mini *mini, char *path)
{
	int		error;
	char	*tmp_key;

	tmp_key = NULL;
	error = 0;
	tmp_key = return_value(mini, path);
	if (tmp_key != NULL)
	{
		error = chdir(tmp_key);
		free(tmp_key);
	}
	if (error != 0)
		print_error(mini, UNSET_HOME);
	return (error);
}

int	builtin_cd(t_mini *mini, t_cmd *cmd)
{
	int	error;

	error = 1;
	if (cmd->str[1] == NULL || ft_strcmp_simple(cmd->str[1], "~") == 0)
		error = do_cd(mini, "HOME");
	else if (ft_strcmp_simple(cmd->str[1], "-") == 0)
		error = do_cd(mini, "OLDPWD");
	else
	{
		error = chdir(cmd->str[1]);
		if (error == -1)
		{
			ft_putstr_fd("shelldone: cd: ", STDERR_FILENO);
			ft_putstr_fd(cmd->str[1], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			return (error);
		}
	}
	update_path(mini);
	update_list_env(mini);
	//concat_lst_env(mini);
	return (error);
}
