/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/24 16:59:43 by anovio-c         ###   ########.fr       */
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

// STRUCTS

// 		Main struct

typedef struct s_mini
{
	char					*line;
	char					**env;
	struct s_lexer			*lexer;
	int						pipes;
	struct s_simple_cmd		*simple_cmd;
}			t_mini;

//		Enum for operators

typedef enum s_operator
{
	PIPE = 1, 		// |
	RED_IN,			// <
	RED_OUT,		// >
	HDOC,			// <<
	RED_OUT_APP,	// >>
}			t_operator;

//		Struct for the lexer/tokenizer

typedef struct s_lexer
{
	char		*str;
	t_operator	token;
	struct s_lexer		*next;
}				t_lexer;

//		Struct for parser

typedef struct s_simple_cmd
{
	char					**str;
	int						(*builtin)(t_mini *, struct s_simple_cmd *);
	int						num_redirections;
	char					*hd_filename;
	t_lexer					*redirections;
	struct s_simple_cmd		*next;
}				t_simple_cmd;

// Test functions

void	ft_print(t_mini *mini);


// Minishell loop

int mini_live(t_mini *mini);


// Lexer

int		lexer_tokenizer(t_mini *mini);
int		put_word(char *str, int i, t_lexer **lst);
int 	find_next_quote(char c, char *str, int i);
int		put_operator(char *str, int i, t_lexer **lst);
int		check_operator(int c);
void	clear_line(t_mini *mini);

// Parser

int		parser(t_mini *mini);
void	count_pipes(t_mini *mini);


// Utils nodes

t_lexer	*ft_new_node(char *str, int token);
void	ft_node_add_back(t_lexer **lst, t_lexer *node);
int		list_add_node(t_lexer **lst, t_operator token, char *str);
t_lexer	*clear_one(t_lexer **lst);
void	del_first_node(t_lexer **lst);

// Random utils

void	check_quotes(char *line);

#endif
