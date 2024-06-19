/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:43:08 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/19 16:30:35 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_fatal_error(t_mini *mini, int keycode)
{
	free_mini(mini);
	if (keycode == MALLOC_ERROR)
		ft_putendl_fd("malloc: cannot allocate memory", STDERR_FILENO);
	else if (keycode == PIPE_ERROR)
		ft_putendl_fd("pipe: Error", STDERR_FILENO);
	else if (keycode == FORK_ERROR)
		ft_putendl_fd("fork: Error", STDERR_FILENO);
	else if (keycode == DUP2_ERROR)
		ft_putendl_fd("dup2: Error", STDERR_FILENO);
	else if (keycode == MAX_HDOC)
		ft_putendl_fd("maximum here-document count exceeded", STDERR_FILENO);
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(2);
}

int	print_error(t_mini *mini, int keycode)
{
	ft_putstr_fd("shelldone: ", STDERR_FILENO);
	if (keycode == MALLOC_ERROR || keycode == PIPE_ERROR
		|| keycode == FORK_ERROR || keycode == DUP2_ERROR
		|| keycode == MAX_HDOC || keycode == UNSET_HOME)
		print_fatal_error(mini, keycode);
	if (keycode == SINTAX_ERROR)
		ft_putstr_fd("syntax error near unexpected token\n", 1);
	else if (keycode == IN_ERROR)
		ft_putstr_fd("in: No such file or directory\n", STDERR_FILENO);
	else if (keycode == OUT_ERROR)
		ft_putstr_fd("out: No such file or directory\n", STDERR_FILENO);
	else if (keycode == CMD_NOT_FOUND_ERROR)
		ft_putstr_fd("command not found\n", STDERR_FILENO);
	else if (keycode == EXECVE_ERROR)
		ft_putstr_fd("execve error\n", STDERR_FILENO);
	else if (keycode == EXIT_ERROR)
	{
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	else if (keycode == UNLINK_ERROR)
		ft_putstr_fd("unlink: No such file or directory\n", STDERR_FILENO);
	else if (keycode == EXPORT_ERROR)
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
	return (mini_reset(mini), EXIT_FAILURE);
}

int	token_error(t_mini *mini, int token)
{
	ft_putstr_fd("shelldone: syntax error near unexpected token ",
		STDERR_FILENO);
	if (token == PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	else if (token == RED_IN)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (token == RED_OUT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (token == HDOC)
		ft_putstr_fd("'<<'\n", STDERR_FILENO);
	else if (token == RED_OUT_APP)
		ft_putstr_fd("'>>'\n", STDERR_FILENO);
	lexer_clear(&mini->lexer);
	mini_reset(mini);
	return (EXIT_FAILURE);
}
