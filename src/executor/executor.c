/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:41 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/02 15:54:01 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_builtin(t_simple_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->builtin == "echo")
		builtin_echo(cmd);
	else if (cmd->builtin == "cd")
		builtin_cd(cmd);
	else if (cmd->builtin == "pwd")
		builtin_pwd(cmd);
	else if (cmd->builtin == "export")
		builtin_export(cmd);
	else if (cmd->builtin == "unset")
		builtin_unset(cmd);
	else if (cmd->builtin == "env")
		builtin_env(cmd);
	else if (cmd->builtin == "exit")
		builtin_exit(cmd);
	else
		return ;
}


int executor(t_mini *mini)
{
	// checkear si es un simple builtin pq se ejecuta en el padre
	// checkear si tiene redirects, si es asi abrir y dup, infile y outfile || HDOC
	// simple cmd
	// multiple cmd
	if (mini->pipes == 0 && check_builtin(mini->simple
	if (mini->pipes == 0)
		simple_command(mini->simple_cmd);
	else

