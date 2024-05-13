/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:36:30 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/13 17:20:11 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_mini *mini, t_cmd *cmd)
{
	int	exit_err;

	exit_err = 0;
	// escalar exit code?
	if (cmd->redirections)
		do_redirections(mini, cmd);
	if (cmd->builtin != NOT_HAVE)
		exit_err = do_builtin(mini, cmd);
	if (cmd->str)
		exit_err = do_cmd(mini, cmd);
	exit(exit_err);
}

int	do_cmd(t_mini *mini, t_cmd *cmd)
{
	char	*cmd_head;
	char	*path;
	//int		error_code;

	cmd_head = cmd->str[0];
	if (cmd->redirections)
		if (do_redirections(mini, cmd))
			exit(0); 
	//printf("inside do cmd\n");
	path = find_check_path(cmd_head, mini->env);
	if (!path)
	{
		printf("%s: ", cmd_head);
		print_error(mini, mini->lexer, CMD_NOT_FOUND_ERROR);
	}
	if (execve(path, cmd->str, mini->env) == -1)
	{
		//path = perror; 
		//Down cooment for control for errors
		print_error(mini, mini->lexer, EXECVE_ERROR);
	}
	exit(0);
}

int	do_builtin(t_mini *mini, t_cmd *cmd)
{
	int	exit;

	exit = 0;
	/*if (cmd->builtin == ECHO)
		exit = builtin_echo(mini, cmd);
	else if (cmd->builtin == CD)
		exit = builtin_cd(mini, cmd);*/
	if (cmd->builtin == PWD)
		exit = builtin_pwd(mini);
	/*else if (cmd->builtin == EXPORT)
		exit = builtin_export(mini, cmd);
	else if (cmd->builtin == UNSET)
		exit = builtin_unset(mini, cmd);
	else if (cmd->builtin == ENV)
		exit = builtin_env(mini, cmd);
	else if (cmd->builtin == EXIT)
		exit = builtin_exit(mini, cmd);*/
	return (exit);
}

void	handle_single_cmd(t_mini *mini, t_cmd *cmd)
{
	int	pid;
	int	status;
	//int	flag = 0;

	// expander
	// comentado para test abajo!
	if (cmd->builtin != NOT_HAVE)
	{	//write(1, "", 1);
		do_builtin(mini, cmd);
		exit(0);
	}
	// hdoc
	//ft_heredoc(mini, mini->cmd);
	pid = fork();
	if (pid == -1)
		print_error(mini, mini->lexer, FORK_ERROR);
	//if (flag == 0)
	//{
	//	printf("STDIN %d STDOUT %d\n", STDIN_FILENO, STDOUT_FILENO);
	//	flag = 1;
	//}
//	if (flag == 1)
//		return ;
	if (pid == 0)
		do_cmd(mini, cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == false)
		mini->error_code = WEXITSTATUS(status);
}
