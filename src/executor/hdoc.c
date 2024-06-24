/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:52 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/12 17:30:22 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status = 0;

static void	check_max_hdoc(t_mini *mini, t_lexer *redirects)
{
	t_lexer	*tmp;
	int		count;

	count = 0;
	tmp = redirects;
	while (tmp)
	{
		if (tmp->token == HDOC)
			count++;
		tmp = tmp->next;
	}
	if (count > 16)
		print_error(mini, MAX_HDOC);
}

int	check_if_exists_hdoc(t_mini *mini, t_cmd *cmd)
{
	t_lexer	*tmp;
	int		error;

	tmp = cmd->redirections;
	check_max_hdoc(mini, tmp);
	error = EXIT_SUCCESS;
	while (tmp)
	{
		if (tmp->token == HDOC)
		{
			if (cmd->hdoc_filename)
				free(cmd->hdoc_filename);
			cmd->hdoc_filename = generate_filename();
			error = check_eof(mini, tmp, cmd->hdoc_filename);
			if (error)
			{
				mini->error_code = error;
				mini_reset(mini);
			}
		}
		tmp = tmp->next;
	}
	return (error);
}

int	check_eof(t_mini *mini, t_lexer *redir, char *hdoc_filename)
{
	int			error;
	char		*str;
	int			len;
	bool		quotes;

	error = EXIT_SUCCESS;
	str = redir->str;
	len = ft_strlen(str) - 1;
	if ((str[0] == '\"' && str[len] == '\"')
		|| (str[0] == '\'' && str[len] == '\''))
	{
		remove_eof_quotes(redir);
		quotes = true;
	}
	else
		quotes = false;
	mini->outside_hdoc = 0;
	mini->inside_hdoc = 1;
	error = open_save_hdoc(mini, redir, hdoc_filename, quotes);
	mini->inside_hdoc = 0;
	mini->flag_hdoc = 1;
	return (error);
}

static void	handle_signals_hdoc(int sig)
{

	if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT)
		g_status = 130;
}

static void	set_up_signals_hdoc(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sa.sa_handler = handle_signals_hdoc;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	open_save_hdoc(t_mini *mini, t_lexer *redir, char *hdoc_filename,
		bool quotes)
{
	char			*line;
	int				fd;

	g_status = 0;
	set_up_signals_hdoc();
	fd = open(hdoc_filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	line = readline(">");
	while (g_status != 130 && line != NULL && ft_strcmp_simple(redir->str, line) != 0
		&& mini->outside_hdoc == 0)
	{
		if (quotes == false)
			line = expand_str_line(mini, line);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline(">");
	}
	free(line);
	close(fd);
	if (mini->outside_hdoc == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
