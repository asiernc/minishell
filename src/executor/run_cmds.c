/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:36:30 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/23 12:28:11 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_mini *mini, t_cmd *cmd)
{
	int	exit_code;

	exit_code = 0;

		printf("simon business\n");
//		char	*result;
//		int		env_counter;
//		result = expanded_string(mini, mini->line);
//		printf("result %p\nresult: _%s_\n", &result, result);
//		printf("mini->line = %s\n", mini->line);
//		env_counter = count_env_variable(mini, mini->line);
//		printf("env_counter %p\nenv_counter: %i\n", &env_counter, env_counter); 
		write(1, "_", 1);
		send_line(mini, mini->line);
		write(1, "_\n", 2);

/*		int	var_existence;
		int	i;
		i = 0;
		printf("mini->line = %s\n", mini->line);
		var_existence = variable_existence(mini, mini->line, &i);
		printf("variable_existence = %i\n", var_existence);*/
		write(1, "l.25\n", 5);
		printf("not anymore\n");

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

int	do_cmd(t_mini *mini, t_cmd *cmd)
{
	char	*cmd_head;
	char	*path;

	cmd_head = cmd->str[0];
	if (cmd->redirections)
		if (do_redirections(mini, cmd))
			exit(1); 
	path = find_check_path(mini, cmd_head, mini->env_cpy); // mandar 127 si no lo encuentra
	if (!path)
		print_error(mini, CMD_NOT_FOUND_ERROR);
	execve(path, cmd->str, mini->env_cpy);
	exit(1);
	//exit(127);
}

int	do_builtin(t_mini *mini, t_cmd *cmd)
{
	int	exit;

	exit = 0;
//	if (mini && cmd)
//		fprintf(stderr, "");
	if (cmd->builtin == ECHO)
		exit = builtin_echo(mini, cmd);
/*	else if (cmd->builtin == CD)
		exit = builtin_cd(mini, cmd);*/
	else if (cmd->builtin == PWD)
		exit = builtin_pwd(mini);
//	else if (cmd->builtin == EXPORT)
//		exit = builtin_export(mini, cmd->str);
//	else if (cmd->builtin == UNSET)
//		exit = builtin_export(mini, cmd->str);//check yourunset
		//exit = builtin_unset(mini, cmd->str);
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
