/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/19 15:14:57 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_var	g_global_var = {0, 0, 0, 0};

static int	save_pwd(t_mini *mini, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			mini->pwd = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			mini->old_pwd = ft_substr(env[i], 7, ft_strlen(env[i]) - 7);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **original_env)
{
	t_mini		mini;

	if ((argc != 1 && argv[0]))
	{
		printf("Don't write any argument\n");
		exit(0);
	}
	mini.env = NULL;
	if (original_env[0])
	{
		create_builtin_lst(&mini, &mini.env, original_env);
		concat_lst_env(&mini);
	}
	init_mini(&mini, original_env);
	save_pwd(&mini, original_env);
	mini_live(&mini);
	return (0);
}
