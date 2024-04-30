/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/30 15:42:18 by anovio-c         ###   ########.fr       */
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
}	t_mini;

//		Enum for operators

enum t_operator
{
	PIPE = 1, 		// |
	RED_IN,			// <
	RED_OUT,		// >
	HDOC,			// <<
	RED_OUT_APP,	// >>
};

//		Struct for the lexer/tokenizer

typedef struct s_lexer
{
	char				*str;
	enum t_operator		token;
	int					num_node;
	struct s_lexer		*next;
}	t_lexer;

//		Struct for parser
// Definición del tipo de función de los comandos
// This is OK ==> t_mini *mini, s_simple_cmd *cmd);
typedef void (*builtin)(void);

typedef struct s_simple_cmd
{
	char					**str;
	builtin					func;
	int						num_redirections;
	char					*hd_filename;
	t_lexer					*redirections;
	struct s_simple_cmd		*next;
}	t_simple_cmd;

typedef struct s_parser
{
	t_lexer			*lexer;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_mini	*mini;
}	t_parser;

// Test functions

void			ft_print(t_mini *mini);
void			ft_print_parser(t_mini *mini);
void			builtin_test(void);



// Minishell loop

int 			mini_live(t_mini *mini);
int				reset(t_mini *mini);

// Lexer

int				lexer_tokenizer(t_mini *mini);
int				put_word(char *str, int i, t_lexer **lst);
int 			find_next_quote(char c, char *str, int i);
int				put_operator(char *str, int i, t_lexer **lst);
int				check_operator(int c);
void			clear_line(t_mini *mini);

// Parser

int				parser(t_mini *mini);
t_parser		init_struct(t_lexer *lexer, t_mini *mini);
t_simple_cmd	*create_cmd(t_parser *parser);
void			redirections(t_parser *parser);

// Parser utils

t_simple_cmd	 *new_simple_cmd(char **str, int num_redirects, t_lexer *redirections);
void			count_pipes(t_mini *mini);
int				count_args(t_lexer *lst);
t_lexer			*move_to_next_cmd(t_lexer *lst);
void			ft_node_add_back_parser(t_simple_cmd **lst, t_simple_cmd *node);
int				check_line(t_mini *mini, int token);

int				lst_size_simple_cmd(t_mini *mini);


// Built-ins

builtin			find_builtin(char *str);


// Utils nodes

t_lexer			*ft_new_node(char *str, int token);
void			ft_node_add_back(t_lexer **lst, t_lexer *node);
int				list_add_node(t_lexer **lst, enum t_operator token, char *str);
t_lexer			*clear_one(t_lexer **lst);
void			del_first_node(t_lexer **lst);
void			delone_node(int num_del, t_lexer **lst);
int				lst_size(t_mini *mini);
void			lst_clear_lexer(t_lexer **lst);

// Random utils

void			check_quotes(char *line);

// Errors

void			print_error(t_mini *mini, t_lexer *lexer, int keycode);
void			parser_token_error(t_mini *mini, int token);

#endif
