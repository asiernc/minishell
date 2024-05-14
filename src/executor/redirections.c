/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:27:35 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/13 21:12:09 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_infile(t_mini *mini, char *filename)
{
	int	fd_in;

	fd_in = open(filename, O_RDONLY);
	//printf("filename %s\n", filename);
	if (fd_in == -1) //posible problema hdoc, si no hay filename, que no lo habra hasta que lo cree, suspendera ejecucion y hara reset.
		print_error(mini, mini->lexer, IN_ERROR);
	/*if (fd_in > 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			print_error(mini, mini->lexer, DUP2_ERROR);
		close(fd_in);
	}*/
	if (fd_in > 0 && dup2(fd_in, STDIN_FILENO) == -1)
		print_error(mini, mini->lexer, DUP2_ERROR);
	if (fd_in > 0)
		close(fd_in);
	return (EXIT_SUCCESS);
}

int	pre_outfile(t_lexer *lex, char *filename)
{
	int	fd_out;

	fd_out = 0;
	//printf("token red %d\n", lex->token);
	if (lex->token == RED_OUT)
		fd_out = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (lex->token == RED_OUT_APP)
		fd_out = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	//printf("fd_out %d\n", fd_out);
	return (fd_out);
}

int	put_outfile(t_mini *mini, t_lexer *lex, char *filename)
{
	int	fd_out;

	fd_out = pre_outfile(lex, filename);
	if (fd_out == -1)
		print_error(mini, mini->lexer, OUT_ERROR);
	/*if (fd_out > 0)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			print_error(mini, mini->lexer, DUP2_ERROR);
		close(fd_out);
	}*/
	if (fd_out > 0 && dup2(fd_out, STDOUT_FILENO) == -1)
		print_error(mini, mini->lexer, DUP2_ERROR);
	if (fd_out > 0)
		close(fd_out);
	return (EXIT_SUCCESS);
}

int do_redirections(t_mini *mini, t_cmd *cmd)
{
	t_lexer	*tmp;

	tmp = cmd->redirections;
	//printf("inside redirects\n");
	//printf("%d token \n", cmd->redirections->token);
	//printf("Token RED_in %d\n", RED_IN);
	while (cmd->redirections)
	{
		if (cmd->redirections->token == RED_IN)
		{
			//printf("RED_IN\n");
			put_infile(mini, cmd->redirections->str);
		}
		else if (cmd->redirections->token == RED_OUT
				|| cmd->redirections->token == RED_OUT_APP)
			put_outfile(mini, cmd->redirections, cmd->redirections->str);
		else if (cmd->redirections->token == HDOC)
			put_infile(mini, cmd->hdoc_filename);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = tmp;
	return (EXIT_SUCCESS);
}

void	have_infile(t_mini *mini, t_lexer *red)
{
	t_lexer	*tmp;

	tmp = red;
	while (red)
	{
		if (red->token == RED_IN)
			mini->count_infiles++;
		red = red->next;
	}
	red = tmp;
}
