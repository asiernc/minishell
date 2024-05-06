/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:41 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/06 12:44:32 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int executor(t_mini *mini)
{
	// checkear si es un simple builtin pq se ejecuta en el padre
	// checkear si tiene redirects, si es asi abrir y dup, infile y outfile || HDOC
	// simple cmd
	// multiple cmd
	int	fds[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (mini->simple_cmd)
	{
		//llamar al expander aqui??
		if (mini->pipes != 0)
			pipe(fds);
		ft_heredoc(mini, mini->simple_cmd);

		//abrir HDOC
		//forks
		//closes
		//

