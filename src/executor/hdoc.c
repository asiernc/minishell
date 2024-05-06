/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:52 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/06 16:12:32 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_filename(void)
{
	static int	i = 1;
	char		*str;

	str = ft_strjoin("./tmp/.tmp_hdoc_file", ft_itoa(i));
	i++;
	return (str);
}

int	create_hdoc(t_mini *mini, t_lexer *redir, char *hdoc_filename, bool quotes)
{
	char	*line;
	int		fd;

	fd = open(hdoc_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	line = readline(">");
	while (line && ft_strcmp(redir->str, line) != 0)
	{
		if (quotes == false)
			line = expand_line(mini, line);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline(">");
	}
	free(line);
	if (!line)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

void	remove_quotes(t_lexer *node)
{
	char	*str;

	str = node->str;
	free(node->str);
	if (str[0] == '\"' || str[0] == '\'')
		node->str = ft_substr(str, 1, ft_strlen(str) - 1);
}

int	check_eof(t_mini *mini, t_lexer *redir, char *hdoc_filename)
{
	int		error;
	int		str;
	int		len;
	bool	quotes;

	error = EXIT_SUCCESS;
	str = redir->str;
	len = ft_strlen(str) - 1;
	if ((str[0] == '\"' && str[len] == '\"')
		|| (str[0] == '\'' && str[len] == '\''))
	{
		remove_quotes(redir);
		quotes = true;
	}
	else
		quotes = false;
	error = create_hdoc(mini, redir, hdoc_filename, quotes);
	return (error);
}

int	ft_heredoc(t_mini *mini, t_simple_cmd *cmd)
{
	t_lexer	*tmp;
	int		error;

	tmp = cmd->redirections;
	error = EXIT_SUCCESS;
	while (cmd->redirections)
	{
		if (cmd->redirections->token == HDOC)
		{
			cmd->hdoc_filename = generate_filename();
			error = check_eof(mini, cmd, cmd->hdoc_filename);
			if (error)
				reset(mini);
		}
		cmd = cmd->next;
	}
	cmd = tmp;
}
