/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:43:08 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/01 11:57:25 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	print_error(t_mini *mini, t_lexer *lexer, int keycode)
{
	ft_putstr_fd("minihell: ", STDERR_FILENO);
	if (keycode == 0)
		ft_putstr_fd("syntax error near unexpected token\n", STDERR_FILENO);
	else if (keycode == 1)
		ft_putstr_fd("malloc: cannot allocate memory\n", STDERR_FILENO);
	if (keycode == 2)
		ft_putstr_fd("in: No such file or directory\n", STDERR_FILENO);
	if (lexer)
		lst_clear_lexer(&lexer); // posiblemente de error de segfault si mandamos error por ejemplo infile.
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
