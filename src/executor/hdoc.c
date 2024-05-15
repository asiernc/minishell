/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:01:52 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/14 21:51:16 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_filename(void)
{
	static int	i = 1;
	char		*str;

	//str = ft_strjoin("src/tmp/hdoc_file", ft_itoa(i));
	str = ft_strjoin("hdoc_file", ft_itoa(i)); // test before expander
	str = ft_strjoin(str, ".c");
	i++;
	return (str);
}

int	create_hdoc(/*t_mini *mini, */t_lexer *redir, char *hdoc_filename, bool quotes)
{
	char	*line;
	int		fd;

	fprintf(stderr, "inside good\n");
	fd = open(hdoc_filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	line = readline(">");
	while (line && ft_strcmp(redir->str, line) != 0)
	{
		if (quotes == false)
			write(1, "", 1);
		//	line = expand_line(mini, line);
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

int	check_eof(t_lexer *redir, char *hdoc_filename)
{
	int			error;
	char		*str;
	int			len;
	bool		quotes;

	error = EXIT_SUCCESS;
	str = redir->str;
	len = ft_strlen(str) - 1;
	// hacer un strchr que encuentre la pareja, si hay alguna comilla no se expande
	// hacer un check quotes, que sea par
	if ((str[0] == '\"' && str[len] == '\"')
		|| (str[0] == '\'' && str[len] == '\''))
	{
		remove_quotes(redir);
		quotes = true;
	}
	else
		quotes = false;
	error = create_hdoc(redir, hdoc_filename, quotes);
	return (error);
}

int	sends_hdoc(t_mini *mini, t_cmd *cmd, int fds[2])
{
	int	fd_in;

//	fd_in = 0;
	fprintf(stderr, "filename %s\n", cmd->hdoc_filename);
	if (mini->flag_hdoc == 1)
	{
		mini->flag_hdoc = 0;
		close(fds[0]);
		fd_in = open(cmd->hdoc_filename, 0644);
	}
	else
		fd_in = fds[0];
	return (fd_in);
}

int	ft_heredoc(t_mini *mini, t_cmd *cmd)
{
	t_lexer	*tmp;
	int		error;
	int		count;

	tmp = cmd->redirections;
	error = EXIT_SUCCESS;
	count = 0;
	while (cmd->redirections)
	{
		if (count >= 16)
			break ;
			//bash: maximum here-document count exceeded == exit (sale de bash)
		if (cmd->redirections->token == HDOC)
		{
			fprintf(stderr, "inside good\n");
			count++;
			cmd->hdoc_filename = generate_filename();
			error = check_eof(mini->cmd->redirections, cmd->hdoc_filename);
			if (error) // error == exitFAILURE
				reset(mini);
		}
		cmd = cmd->next;
	}
	cmd->redirections = tmp;
	mini->flag_hdoc = 1;
	return (error);
}
