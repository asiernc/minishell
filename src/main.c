/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:37:48 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/18 18:08:12 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini		mini;
	t_builtin	*lst_env;

	if (argc != 1 && argv[0])
	{
		printf("Don't write any argument");
		exit(0);
	}
	lst_env = NULL;
	mini.original_env = env;
	mini.env = create_env(&mini, lst_env);
	get_pwd(&mini);
	//printf("no %s%s\n", argv[0], env[1]);
	mini_live(&mini);
	return (0);
}
