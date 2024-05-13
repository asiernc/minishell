/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:47:43 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/11 15:36:14 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pre_executor(t_mini *mini)
{
	printf("IIIIIIIIIIIIIIIIIIIIIII\n");
	if (mini->cmd->next == NULL && mini->pipes == 0)
		handle_single_cmd(mini, mini->cmd);
	else
		executor(mini);
	return (0);
}


// esta bien que pase por env de inicio, pero valorar de donde leer, 
// si de env de shell o de env de nuestra shell

char	*find_check_path(char *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;
	char	*tmp;

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
