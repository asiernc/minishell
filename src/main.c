/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/19 17:21:41 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_var	g_global_var = {0, 0, 0, 0};

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
	if (!save_pwd(&mini, original_env))
		print_error(&mini, RANDOM);
	mini_live(&mini);
	return (0);
}
