/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:41 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/16 16:51:30 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in)
{
	// unsigned ??
	static int	i = 0; //valorar sobrescribir guardandome el ultimo pid que es el
	// contiene el error code

	fprintf(stderr, "FORK\n");
	mini->pid[i] = fork();
	if (mini->pid[i] == -1)
		print_error(mini, mini->lexer, FORK_ERROR);
	if (mini->pid[i] == 0)
		ft_dup(mini, cmd, fds, fd_in);
	i++;
	close(fds[1]);
	return (EXIT_SUCCESS);
}

void	ft_dup(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in)
{
	if (cmd->previous)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			print_error(mini, mini->lexer, DUP2_ERROR);
		close(fds[0]);
	}
	if (cmd->next)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			print_error(mini, mini->lexer, DUP2_ERROR);
		close(fds[1]);
	}
	if (cmd->previous)
		close(fd_in);
	ft_exec_cmd(mini, cmd);
}


void	wait_pipes(t_mini *mini, int *pid, int pipes)
{
	int	i;
	int	status;

	i = 0;
	while (i <= pipes)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status) == false)
		mini->error_code = WEXITSTATUS(status);
}

int executor(t_mini *mini)
{
	int	fds[2];
	int	fd_in;
	int	count_pipes;

	count_pipes = mini->pipes;
	mini->pid = ft_calloc((count_pipes + 2), sizeof(int));
	if (!mini->pid)
		print_error(mini, mini->lexer, MALLOC_ERROR);
	fd_in = STDIN_FILENO;
	while (mini->cmd)
	{
		//llamar al expander aqui??
		if (mini->cmd->next && pipe(fds) == -1) //mini->cmd->next
			print_error(mini, mini->lexer, PIPE_ERROR);
		ft_heredoc(mini, mini->cmd);
		ft_fork(mini, mini->cmd, fds, fd_in);
		if (mini->cmd->previous != NULL)
			close(fd_in);
		fd_in = sends_hdoc(mini, mini->cmd, fds);
		if (mini->cmd->next)
			mini->cmd = mini->cmd->next;
		else
			break ;
	}
	wait_pipes(mini, mini->pid, mini->pipes);
	close(fd_in);
	return (0);
	// hacer limpieza recursiva o guardar/mover puntero cmd nodo al primero para free
}
