/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/20 17:53:23 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **original_env)
{
	t_mini		mini;
	t_var		g_var = {0, 0, 0, 0};

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
	init_mini(&mini, original_env, g_var);
	save_pwd(&mini, original_env);
	mini_live(&mini, g_var);
	return (0);
}
