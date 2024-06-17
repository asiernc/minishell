/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/17 14:20:49 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_var	g_global_var = {0, 0, 0, 0};

int	main(int argc, char **argv, char **envp)
{
	t_mini		mini;

	if ((argc != 1 && argv[0]))
	{
		printf("Don't write any argument\n");
		exit(0);
	}
	mini.env = NULL;
	if (envp[0])
	{
		create_builtin_lst(&mini, &mini.env, envp);
		concat_lst_env(&mini);
	}
	init_mini(&mini, envp);
	mini_live(&mini);
	return (0);
}
