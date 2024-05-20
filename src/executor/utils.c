/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:47:43 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/18 17:22:35 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pre_executor(t_mini *mini)
{
	if (mini->pipes == 0)
		handle_single_cmd(mini, mini->cmd);
	else
		executor(mini);
	return (0);
}

char	*generate_filename(void)
{
	static int	i = 1;
	char		*str;

	str = ft_strjoin("hdoc_tmp_file", ft_itoa(i));
	str = ft_strjoin(str, ".c");
	i++;
	return (str);
}

void	remove_eof_quotes(t_lexer *node)
{
	char	*str;
	
	str = node->str;
	free(node->str);
	if (str[0] == '\"' || str[0] == '\'')
		node->str = ft_substr(str, 1, ft_strlen(str) -1);
}

// esta bien que pase por env de inicio, pero valorar de donde leer, 
// si de env de shell o de env de nuestra shell
// hacer otro loop con las env de simon



// mandar 127 is command not found
char	*find_check_path(char *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;
	char	*tmp;

	//valorar hacer access por el caso que nos den la ruta absoluta example ./bin/var/cat
	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	tmp = ft_substr(*env, 5, ft_strlen(*env) - 5);
	paths = ft_split(tmp, ':');
	free(tmp);
	tmp = ft_strjoin("/", cmd);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, tmp);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		free(cmd_path);
		paths++;
	}
	free(tmp);
	return (cmd_path);
}
