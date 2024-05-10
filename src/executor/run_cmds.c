/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:36:30 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/10 14:10:13 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_mini *mini, t_cmd *cmd)
{
	int	exit;
	// escalar exit code?
	if (cmd->redirections)
		do_redirections(cmd);
	if (cmd->builtin != NOT_HAVE)
		exit = do_builtin(mini, cmd);
	if (cmd->str)
		exit = do_cmd(mini, cmd);
	exit(exit);
}

char	*find_check_path(char *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;
	char	*tmp;

	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	tmp = ft_substr(*env, 5, ft_strlen(*env) - 5);
	paths = ft_split(tmp, ':');
	free(tmp);
	tmp = ft_strjoin("/", cmd);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, tmp);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		free(cmd_path);
		paths++;
	}
	free(tmp);
	return (cmd_path);
}

int	do_cmd(t_mini *mini, t_cmd *cmd)
{
	char	*cmd;
	char	*path;
	//int		error_code;

	cmd = cmd->str[0];
	path = find_check_path(cmd, mini->env);
	if (!path)
	{
		printf("%s: ", cmd);
		print_error(mini, mini->lexer, CMD_NOT_FOUND_ERROR);
	}
	if (execve(path, cmd->str, mini->env) == -1)
	{
		path = perror;
		print_error(mini, mini->lexer, EXECVE_ERROR);
	}
	return (0);
}

int	do_builtin(t_mini *mini, t_cmd *cmd)
{
	int	exit;

	if (cmd->builtin == ECHO)
		exit = builtin_echo(mini, cmd);
	else if (cmd->builtin == CD)
		exit = builtin_cd(mini, cmd);
	else if (cmd->builtin == PWD)
		exit = builtin_pwd(mini, cmd);
	else if (cmd->builtin == EXPORT)
		exit = builtin_export(mini, cmd);
	else if (cmd->builtin == UNSET)
		exit = builtin_unset(mini, cmd);
	else if (cmd->builtin == ENV)
		exit = builtin_env(mini, cmd);
	else if (cmd->builtin == EXIT)
		exit = builtin_exit(mini, cmd);
	return (exit);
}

void	handle_single_cmd(t_mini *mini, t_cmd *cmd)
{
	int	pid;
	int	*status;

	// expander
	if (cmd->builtin != NOT_HAVE)
		do_builtin(mini, cmd);
	// hdoc
	ft_heredoc(mini, mini->cmd);
	pid = fork();
	if (pid == -1)
		print_error(mini, mini->lexer, FORK_ERROR);
	if (pid == 0)
		do_cmd(mini, cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == false)
		mini->error_code = WEXITSTATUS(status);
}
