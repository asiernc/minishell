/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:41 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/06 16:57:43 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_fork(t_mini *mini, t_simple_cmd *cmd, int fds[2], int fd_in)
{
	static int	i = 0;

	mini->pid[i] = fork();
	if (mini->pid[i] == -1)



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
		if (mini->pipes != 0 && pipe(fds) == -1)
			print_error(mini, mini->lexer, PIPE_ERROR);
		ft_heredoc(mini, mini->simple_cmd);
		ft_fork(mini, mini->simple_cmd, fds, fd_in);
		//abrir HDOC
		//forks
		//closes
		//







































int	ft_fork(t_tools *tools, int end[2], int fd_in, t_simple_cmds *cmd)
{
	static int	i = 0;

	if (tools->reset == true)
	{
		i = 0;
		tools->reset = false;
	}
	tools->pid[i] = fork();
	if (tools->pid[i] < 0)
		ft_error(5, tools);
	if (tools->pid[i] == 0)
		dup_cmd(cmd, tools, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}


void	dup_cmd(t_simple_cmds *cmd, t_tools *tools, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, tools);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, tools);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, tools);
}
