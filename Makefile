# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 11:09:08 by anovio-c          #+#    #+#              #
#    Updated: 2024/05/10 20:02:13 by asiercara        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	gcc
INCL	 	=	includes
CFLAGS		=	-Wall -Wextra -Werror -g -I$(INCL)
RM			=	rm -f
LIBFT		=	libft/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)

SRCDIR		=	src/
LEXERDIR	=	src/lexer/
UTILSDIR	=	src/utils/
OBJDIR		=	build/obj/

SRC			=	src/main.c 						\
				src/lexer/tokenizer.c			\
				src/lexer/utils_lexer.c			\
				src/lexer/utils_nodes.c			\
				src/lexer/utils_nodes_aux.c		\
				src/parser/parser.c				\
				src/parser/redirections.c		\
				src/parser/utils_parser.c		\
				src/parser/utils_nodes.c		\
				src/executor/executor.c			\
				src/executor/hdoc.c				\
				src/executor/run_cmds.c			\
				src/executor/utils.c			\
				src/utils/utils.c				\
				src/errors/parser_errors.c

#OBJS		=	$(addprefix $(OBJDIR), $(notdir $(patsubst %.c, %.o, $(src))))
OBJS		= 	$(SRC:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) Makefile #norm
				@$(CC) $(CFLAGS) -L$(LIBFT) -o $(NAME) $(OBJS) -lft -lreadline
				@echo "Linked into executable \033[0;32mminishell\033[0m with norminette \033[0;32mOK\033[0m."

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)."

#$(OBJDIR)%.o:: $(PATHS)%.c
.c.o:
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo "Compiling $<."

norm:
				norminette -R CheckForbiddenSourceHeader $(SRC)
				norminette -R CheckDefine $(INCL)

clean:
				@$(MAKE) clean -s -C $(LIBFT)
				@echo "Clean libft."
				@$(RM) $(OBJS)
				@echo "Removed object files."

fclean:			clean
				@$(MAKE) fclean -s -C $(LIBFT)
				@echo "Full clean libft."
				@$(RM) $(NAME)
				@echo "Removed executable."

re:				fclean all

PHONY:			all clean fclean re norm
