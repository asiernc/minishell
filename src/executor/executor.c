/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:41 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/06 08:22:32 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_filename(void)
{
	static int	i = 1;
	char		*str;

	str = ft_strjoin("./tmp/.tmp_heredoc_file", ft_itoa(i));
	i++;
	return (str);
}

int	create_heredoc(t_mini *mini, t_simple_cmd *cmd, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	line = readline(">");
	while (line && 

int	ft_heredoc(t_mini *mini, t_simple_cmd *cmd)
{
	t_lexer	*tmp;
	int		error;

	tmp = cmd->redirections;
	error = EXIT_SUCCESS;
	while (tmp)
	{
		if (tmp->token == HDOC)
			tmp->filename = generate_filename();
		error = create_heredoc(mini, cmd, tmp->filename);

int executor(t_mini *mini)
{
	// checkear si es un simple builtin pq se ejecuta en el padre
	// checkear si tiene redirects, si es asi abrir y dup, infile y outfile || HDOC
	// simple cmd
	// multiple cmd
	int	fds[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (mini->simple_cmd)
	{
		//llamar al expander aqui??
		if (mini->pipes != 0)
			pipe(fds);
		ft_heredoc(mini, mini->simple_cmd);

		//abrir HDOC
		//forks
		//closes
		//

