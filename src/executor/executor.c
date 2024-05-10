/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:41 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/10 14:10:22 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_mini *mini, t_cmd *cmd)
{
	char	*cmd;
	char	*path;

	cmd = cmd->str[0];
	path = find_check_path(cmd, mini->env);
	if (!path)
	{
		printf("%s: ", cmd); // mirar como $? == 127, como escalar el codigo error
		print_error(mini, mini->lexer, CMD_NOT_FOUND_ERROR);
	}
	if (execve(path, cmd->str, mini->env) == -1)
	{
		path = perror;
		print_error(mini, mini->lexer, EXECVE_ERROR);
	}
}

void	ft_dup(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in)
{
	static int	i = 0;

	//first cmd
	if (i == 0 && dup2(fd_in, STDIN_FILENO) == -1)
		print_error(mini, mini->lexer, DUP2_ERROR);
	close(fds[1]);
	// last cmd
	if (cmd->next == NULL && dup2(fds[1], STDOUT_FILENO) == -1)
		print_error(mini, mini->lexer, DUP2_ERROR);
	close(fds[0]);
	ft_exec_cmd(mini, cmd);
}


int	ft_fork(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in)
{
	static int	i = 0; //valorar sobrescribir guardandome el ultimo pid que es el
	// contiene el error code

	mini->pid[i] = fork();
	if (mini->pid[i] == -1)
		print_error(mini, mini->lexer, FORK_ERROR);
	if (mini->pid[i] == 0)
		ft_dup(mini, cmd, fds, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

void	wait_pipes(t_mini *mini, int *pid, int pipes)
{
	int	i;
	int	*status;

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
	// simple cmd
	// multiple cmd
	int	fds[2];
	int	fd_in;
	int	count_pipes;

	count_pipes = mini->pipes;
	mini->pid = ft_calloc((count_pipes + 2) * sizeof(int));
	if (!mini->pid)
		print_error(mini, mini->lexer, MALLOC_ERROR);
	fd_in = STDIN_FILENO;
	while (mini->cmd)
	{
		//llamar al expander aqui??
		if (count_pipes > 0 && pipe(fds) == -1) //mini->cmd->next
			print_error(mini, mini->lexer, PIPE_ERROR);
		ft_heredoc(mini, mini->cmd);
		ft_fork(mini, mini->cmd, fds, fd_in);
		close(fds[1]);
		fd_in = sends_hdoc(mini, mini->cmd, fds);
		if (mini->cmd->next)
			mini->cmd = mini->cmd->next;
		else
			break ;
		count_pipes--;
	}
	wait_pipes(mini, mini->pid, mini->pipes);
}



int	cmd_not_found(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (127);
}
