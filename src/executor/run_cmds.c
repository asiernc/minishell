/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:36:30 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/18 17:24:40 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_mini *mini, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections)
		do_redirections(mini, cmd);
	if(cmd->builtin != NOT_HAVE)
	{
		exit_code = do_builtin(mini, cmd);
		exit(exit_code);
	}
	if (cmd->str)
		exit_code = do_cmd(mini, cmd);
	exit(exit_code);
}

/*int	do_cmd(t_mini *mini, t_cmd *cmd)
{
	char	*cmd_head;
	char	*path;

	cmd_head = cmd->str[0];
	path = find_check_path(mini, cmd_head, mini->env_cpy); // mandar 127 si no lo encuentra
	if (!path)
		print_error(mini, CMD_NOT_FOUND_ERROR);
	execve(path, cmd->str, mini->env_cpy);
	exit(1);
	//exit(127);
}*/

// mandar 127 is command not found
int	do_cmd(t_mini *mini, t_cmd *cmd_lst)
{
	char	**env;
	char	**paths;
	char	*cmd_path;
	char	*tmp;

	env = mini->env_cpy;
	//valorar hacer access por el caso que nos den la ruta absoluta example ./bin/var/cat
	if (!access(mini->cmd->str[0], F_OK | X_OK))
		execve(mini->cmd->str[0], mini->cmd->str, mini->env_cpy);
	while (*env && !ft_strnstr(*env, "PATH", 5))
		env++;
	tmp = ft_substr(*env, 5, ft_strlen(*env) - 5);
	paths = ft_split(tmp, ':');
	free(tmp);
	tmp = ft_strjoin("/", cmd_lst->str[0]);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, tmp);
		if (!cmd_path)
			print_error(mini, 2);
		if (access(cmd_path, F_OK | X_OK) == 0)
			execve(cmd_path, mini->cmd->str, mini->env_cpy);
		free(cmd_path);
		paths++;
	}
	free(tmp);
	return (127);
}

int	do_builtin(t_mini *mini, t_cmd *cmd)
{
	int	exit;

	exit = 0;
//	if (mini && cmd)
//		fprintf(stderr, "");
	//if (cmd->builtin == ECHO)
	//	exit = builtin_echo(mini, cmd);
/*	else if (cmd->builtin == CD)
		exit = builtin_cd(mini, cmd);*/
	if (cmd->builtin == PWD)
		exit = builtin_pwd(mini);
	else if (cmd->builtin == EXPORT)
		exit = builtin_export(mini, cmd);
	else if (cmd->builtin == UNSET)
		//exit = builtin_export(mini, cmd->str);//check yourunset
		exit = builtin_unset(mini, &mini->env, cmd);
	else if (cmd->builtin == ENV)
		exit = builtin_env(mini);
	else if (cmd->builtin == EXIT)
		exit = builtin_exit(mini, cmd);
	return (exit);
}

void	handle_single_cmd(t_mini *mini, t_cmd *cmd)
{
	int	pid;
	int	status;

	// expander
	// comentado para test abajo!
	if (cmd->builtin != NOT_HAVE)
	{
		do_builtin(mini, cmd);
		mini_reset(mini);
	}
	check_if_exists_hdoc(mini, mini->cmd);
	pid = fork();
	if (pid == -1)
		print_error(mini, FORK_ERROR);
	if (pid == 0)
		ft_exec_cmd(mini, cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == false)
		mini->error_code = WEXITSTATUS(status);
}
