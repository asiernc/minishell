/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:43:08 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/14 11:20:51 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	print_error(t_mini *mini, t_lexer *lexer, int keycode)
{
	ft_putstr_fd("minihell: ", STDERR_FILENO);
	if (keycode == SINTAX_ERROR)
		ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
	else if (keycode == MALLOC_ERROR)
		ft_putstr_fd("malloc: cannot allocate memory\n", STDERR_FILENO);
	else if (keycode == IN_ERROR)
		ft_putstr_fd("in: RNo such file or directory\n", STDERR_FILENO);
	else if (keycode == OUT_ERROR)
		ft_putstr_fd("out: RNo such file or directory\n", STDERR_FILENO);
	else if (keycode == PIPE_ERROR)
		ft_putstr_fd("pipe: Error\n", STDERR_FILENO);
	else if (keycode == FORK_ERROR)
		ft_putstr_fd("fork: Error\n", STDERR_FILENO);
	else if (keycode == DUP2_ERROR)
		ft_putstr_fd("dup2: Error\n", STDERR_FILENO);
	else if (keycode == CMD_NOT_FOUND_ERROR)
		ft_putstr_fd("command not found\n", STDERR_FILENO);
	else if (keycode == EXECVE_ERROR)
		ft_putstr_fd("execve error\n", STDERR_FILENO);
	if (lexer)//test
		printf("");//test
	if (mini->lexer)
		lst_clear_lexer(&mini->lexer); // posiblemente de error de segfault si mandamos error por ejemplo infile.
	//if (mini->simple_cmd)
	//	lst_clear_parser(&mini->simple_cmd);
	reset(mini);
}

void	parser_token_error(t_mini *mini, int token)
{
	ft_putstr_fd("minihell: syntax error near unexpected token ", STDERR_FILENO);
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
	lst_clear_lexer(&mini->lexer);
	reset(mini);
}
