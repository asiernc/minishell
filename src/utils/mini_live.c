/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asiercara <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:52:42 by asiercara         #+#    #+#             */
/*   Updated: 2024/05/29 17:34:40 by asiercara        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// this function is for do the cycle of live for every line receives from readline

int	mini_live(t_mini *mini)
{
	// valorar hacer un bucle para no forzar a que entre dentor de una funcion de otra de otra de otra
	//init_mini(mini);
	mini->line = readline("shelldone 🔥 >");
	clear_line(mini);
	if (mini->line == NULL) // uede que segfault este aqui
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (mini->line[0] == '\0')
		mini_reset(mini);
	add_history(mini->line);
	if (!check_quotes_is_married(mini->line))
		print_error(mini, 1);
	if (!lexer_tokenizer(mini))// != 0)
		print_error(mini, 1);
	parser(mini);
	pre_executor(mini);
	//free and reset
	mini_reset(mini);
	return (0);
}

void	init_mini(t_mini *mini, char **env)
{
	t_builtin	*lst_env;

	lst_env = NULL;
	mini->line = NULL;
	mini->lexer = NULL;
	mini->cmd = NULL;
	mini->flag_hdoc = 0;
	mini->pid = NULL;
	mini->original_env = env;
	g_global_var.inside_cmd = 0;
	g_global_var.inside_hdoc = 0;
	g_global_var.outside_hdoc = 0;
	mini->env = create_builtin_lst(mini, lst_env, env);
	concat_lst_env(mini);
	/*int	i = 0;
	printf("_______________________\n");
	while (mini->env_cpy[i] != NULL) {
        printf("%s\n", mini->env_cpy[i]);
        i++;
    }
	printf("_______________________\n");*/
	/*i = 0;
	printf("_______________________\n");
	while (mini->original_env[i] != NULL) {
        printf("%s\n", mini->original_env[i]);
        i++;
    }
	printf("_______________________\n");*/
	init_signals();
	get_pwd(mini);
	//cd exit success get current directory pwd = getcurrent directory
}

void	lst_clear_cmds(t_cmd **cmd)
{
	t_cmd	*tmp_cmd;
	t_lexer	*tmp_redirects;

    if (!*cmd)
        return;
    tmp_cmd = *cmd;
    while (tmp_cmd && tmp_cmd->previous)
        tmp_cmd = tmp_cmd->previous;
	*cmd = tmp_cmd;
	while (*cmd)
	{ 
		tmp_cmd = (*cmd)->next;
		tmp_redirects = (*cmd)->redirections;
		lexer_clear(&tmp_redirects);
		if ((*cmd)->hdoc_filename)
		{
			if (unlink((*cmd)->hdoc_filename) == -1)
				print_error(NULL, 12);
			free((*cmd)->hdoc_filename);
		}
		if ((*cmd)->str)
			free_cmd_line((*cmd)->str);
		free(*cmd);
		*cmd = tmp_cmd;
	}
	*cmd = NULL;
}

// function for free all and call another time mini_live for create a loop

int	mini_reset(t_mini *mini)
{
	// HACERLE FREE A PWD, TIENE MALLOC
	
	if (mini->cmd)
		lst_clear_cmds(&mini->cmd);
	if (mini->line)
		free(mini->line);
	if (mini->pid)
		free(mini->pid);
	init_mini(mini, mini->original_env);
	mini_live(mini);
	return (0);
}


