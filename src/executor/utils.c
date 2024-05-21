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


// mandar 127 is command not found
char	*find_check_path(t_mini *mini, char *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;
	char	*tmp;

	//valorar hacer access por el caso que nos den la ruta absoluta example ./bin/var/cat
	if (!access(mini->cmd->str[0], F_OK | X_OK))
		execve(mini->cmd->str[0], mini->cmd->str, mini->env_cpy);
	while (*env && !ft_strnstr(*env, "PATH", 5))
		env++;
	tmp = ft_substr(*env, 5, ft_strlen(*env) - 5);
	paths = ft_split(tmp, ':');
	free(tmp);
	tmp = ft_strjoin("/", cmd);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, tmp);
		fprintf(stderr, "PATH = %s\n", cmd_path);
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

t_builtin	*find_node_path(t_builtin *lst_env)
{
	t_builtin	*tmp;

	tmp = lst_env;
	while (tmp)
	{
		if (ft_strcmp(lst_env->key, "PATH") == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	concat_lst_env(t_mini *mini)
{
	t_builtin	*tmp;
	int		len;
	int		i;

	tmp = mini->env;
	len = ft_lstsize_builtin(tmp);
	mini->env_cpy = (char **)malloc((len + 1) * sizeof(char *));
	if (!mini->env_cpy)
		print_error(mini, 2);
	i = 0;
	while (tmp)
	{
		mini->env_cpy[i] = (char *)malloc((ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2) * sizeof(char));
		if (!mini->env_cpy[i])
		{
			while (i > 0 )
			{
				free(mini->env_cpy[i]);
				i--;
			}
			free(mini->env_cpy);
			print_error(mini, 2);
		}
		mini->env_cpy[i] = ft_strjoin(tmp->key, ft_strjoin("=", tmp->value));
		tmp = tmp->next;
		i++;
	}
	mini->env_cpy[len] = NULL;
}

/*char	*check_path(char *cmd, t_builtin *lst_env)
{
	char	**paths;
	char	*cmd_path;
	char	*tmp;
	t_builtin	*node_path;

	//valorar hacer access por el caso que nos den la ruta absoluta example ./bin/var/cat
	node_path = find_path(lst_env);
	paths = ft_split(node_path->value, ':');
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
}*/