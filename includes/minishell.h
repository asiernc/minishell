/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/23 10:03:15 by asiercara        ###   ########.fr       */
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

typedef enum s_tokens
{
	PIPE = 1,
	GREATER,
	DOUBLE_GREATER,
	LESS,
	DOUBLE_LESS,
}			t_tokens;

typedef struct s_lexer
{
	char		*str;
	t_tokens	*token;
	int			i;
	struct s_lexer		*previous;
	struct s_lexer		*next;
}				t_lexer;

typedef struct s_mini
{
	char	*line;
	char	**env;
	t_lexer	*lexer;
}			t_mini;

int mini_live(t_mini *mini);

#endif
