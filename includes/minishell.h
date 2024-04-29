/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/04/26 19:04:09 by simarcha         ###   ########.fr       */
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
// 		This is the structure that will contain everything at the end
typedef struct s_mini
{
	char					*line;//the line inputs by the user
	char					**env;//env in the main
	struct s_lexer			*lexer;
	int						pipes;//count the pipes to execute pipe + 1 commands 
	struct s_simple_cmd		*simple_cmd;
}	t_mini;

//		Enum for operators
//		we gave a number to know which kind of operator/token it is
//		0 if it's not
typedef enum s_operator
{
	PIPE = 1, 		// |
	RED_IN,			// <
	RED_OUT,		// >
	HDOC,			// <<
	RED_OUT_APP,	// >>
}	t_operator;

//		Struct for the lexer/tokenizer
//		The goal of this structure is to divide every word and to assign a value
//		We have the word
//		we assign it a number to make the difference between a token and everything else
//		and we gave it a number to know where it's located in the line
typedef struct s_lexer
{
	char				*str;//one word of the line
	t_operator			token;//the id number to know if it's a token or a word
	int					num_node;//the number of the token/word in the line inputed
	struct s_lexer		*next;
}	t_lexer;

//		Struct for parser
typedef struct s_simple_cmd
{
	char					**str;
	int						(*builtin)(t_mini *, struct s_simple_cmd *);//NOT SURE: the name of the builtin to call
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


// Minishell loop

int				mini_live(t_mini *mini);


// Lexer

int				lexer_tokenizer(t_mini *mini);
int				put_word(char *str, int i, t_lexer **lst);
int				find_next_quote(char c, char *str, int i);
int				put_operator(char *str, int i, t_lexer **lst);
int				check_operator(int c);
void			clear_line(t_mini *mini);

// Parser

int				parser(t_mini *mini);
t_parser		init_struct(t_lexer *lexer, t_mini *mini);
t_simple_cmd	*create_cmd(t_parser *parser);
void			redirections(t_parser *parser);

// Parser utils

t_simple_cmd	*new_simple_cmd(char **str, int num_redirects, t_lexer *redirections);
void			count_pipes(t_mini *mini);
int				count_args(t_lexer *lst);
t_lexer			*move_to_next_cmd(t_lexer *lst);
void			ft_node_add_back_parser(t_simple_cmd **lst, t_simple_cmd *node);

int				lst_size_simple_cmd(t_mini *mini);




// Utils nodes

t_lexer			*ft_new_node(char *str, int token);
void			ft_node_add_back(t_lexer **lst, t_lexer *node);
int				list_add_node(t_lexer **lst, t_operator token, char *str);
t_lexer			*clear_one(t_lexer **lst);
void			del_first_node(t_lexer **lst);
void			delone_node(int num_del, t_lexer **lst);
int				lst_size(t_mini *mini);

// Random utils

void			check_quotes(char *line);

#endif
