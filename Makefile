# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 11:09:08 by anovio-c          #+#    #+#              #
#    Updated: 2024/04/23 15:41:21 by anovio-c         ###   ########.fr        #
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
OBJDIR		=	obj/

SRC			=	src/main.c 			\
				src/tokens.c		\
				src/utils_nodes.c

OBJS		=	$(SRC:%.c=%.o)

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT_A) Makefile #norm
				@$(CC) $(CFLAGS) -L$(LIBFT) -lft -o $(NAME) $(OBJS) -lft -lreadline
				@echo "Linked into executable \033[0;32mminishell\033[0m with norminette \033[0;32mOK\033[0m."

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)."

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
