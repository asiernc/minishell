/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:38:37 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/13 10:50:51 by anovio-c         ###   ########.fr       */
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
# include <stdbool.h>

// STRUCTS

// 		Main struct

typedef struct s_mini
{
	char					*line;
	char					**env;
	// struct env
	// strcut export
	struct s_lexer			*lexer;
	int						pipes;
	int						flag_hdoc;
	int						*pid;
	int						error_code;
	struct s_cmd		*cmd;
}	t_mini;

//		Enum for builtins

enum	e_builtins
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NOT_HAVE,
};

//		Enum for code errors

enum	e_error_codes
{
	SINTAX_ERROR = 1,
	MALLOC_ERROR,		// allocation error
	IN_ERROR,			// infile error
	OUT_ERROR,			// outfile error
	PIPE_ERROR,
	FORK_ERROR,
	DUP2_ERROR,
	CMD_NOT_FOUND_ERROR,
	EXECVE_ERROR,
};
//		Enum for operators

enum e_operator
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
	enum e_operator		token;
	int					num_node;
	struct s_lexer		*next;
}	t_lexer;

//		Struct for parser

//typedef void (*builtin)(t_mini *mini, t_cmd *cmd);

typedef struct s_cmd
{
	char					**str;
	enum e_builtins			builtin;
	int						num_redirections;
	char					*hdoc_filename;
	t_lexer					*redirections;
	struct s_cmd		*next;
	struct s_cmd		*previous;
}	t_cmd;

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
t_cmd			*create_cmd(t_parser *parser);
void			redirections(t_parser *parser);
void			lst_clear_parser(t_cmd **lst);

// Parser utils

t_cmd			 *new_cmd(char **str, int num_redirects, t_lexer *redirections);
int				prepare_builtin(char *str);
void			count_pipes(t_mini *mini);
int				count_args(t_lexer *lst);
t_lexer			*move_to_next_cmd(t_lexer *lst);
void			ft_node_add_back_parser(t_cmd **lst, t_cmd *node);
int				check_line(t_mini *mini, int token);

int				lst_size_cmd(t_mini *mini);


// Built-ins

//builtin			find_builtin(char *str);


// Executor

int				pre_executor(t_mini *mini);
void			handle_single_cmd(t_mini *mini, t_cmd *cmd);

int				executor(t_mini *mini);
int				ft_fork(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in);
void			ft_dup(t_mini *mini, t_cmd *cmd, int fds[2], int fd_in);
void			ft_exec_cmd(t_mini *mini, t_cmd *cmd);
char			*find_check_path(char *cmd, char **env);
int				do_cmd(t_mini *mini, t_cmd *cmd);
int				do_builtin(t_mini *mini, t_cmd *cmd);
void			handle_single_cmd(t_mini *mini, t_cmd *cmd);
void			wait_pipes(t_mini *mini, int *pid, int pipes);

// Redirections

int				do_redirections(t_mini *mini, t_cmd *cmd);
int				put_infile(t_mini *mini, char *filename);
int				pre_outfile(t_lexer *lex, char *filename);
int				put_outfile(t_mini *mini, t_lexer *lex, char *filename);



// Hdoc

int				ft_heredoc(t_mini *mini, t_cmd *cmd);
char			*generate_filename(void);
int				check_eof(t_mini *mini, t_lexer	*redir, char *hdoc_filename);
int				create_hdoc(t_mini *mini, t_lexer *redir, char *hdoc_filename, bool quotes);
void			remove_quotes(t_lexer *node);
int				sends_hdoc(t_mini *mini, t_cmd *cmd, int fds[2]);

// Utils nodes

t_lexer			*ft_new_node(char *str, int token);
void			ft_node_add_back(t_lexer **lst, t_lexer *node);
int				list_add_node(t_lexer **lst, enum e_operator token, char *str);
t_lexer			*clear_one_node(t_lexer **lst);
void			del_first_node(t_lexer **lst);
void			delone_node(int num_del, t_lexer **lst);
int				lst_size_lexer(t_mini *mini);
void			lst_clear_lexer(t_lexer **lst);

// Random utils

void			check_quotes(char *line);

// Errors

void			print_error(t_mini *mini, t_lexer *lexer, int keycode);
void			parser_token_error(t_mini *mini, int token);

#endif
