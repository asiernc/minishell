/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/23 15:15:24 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> // Open 
# include <string.h> //Macros
# include <dirent.h>
# include <sys/wait.h> // wait waitpid
# include <limits.h> // macros??
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

//structs

typedef enum s_operator
{
	PIPE = 1,
	RED_IN,
	RED_OUT,
	HDOC,
	RED_OUT_APP,
}			t_operator;

// | < > << >> order

typedef struct s_lexer
{
	char		*str;
	t_operator	token;
	struct s_lexer		*next;
}				t_lexer;

typedef struct s_mini
{
	char	*line;
	char	**env;
	t_lexer	*lexer;
}			t_mini;

int mini_live(t_mini *mini);


// Utils

int		ft_new_node(char *str, int token);
void	ft_node_add_back(t_lexer **lst, t_operator *node);
int		list_add_node(t_lexer **lst, t_operator token, char *str);

//src/verify_quotes.c
int		print_error(char *str);
void	check_quotes(char *line);

#endif
