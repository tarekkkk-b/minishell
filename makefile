# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:17:34 by tabadawi          #+#    #+#              #
#    Updated: 2024/06/10 17:15:59 by tabadawi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
RLFLAGS		=	-lreadline -lhistory
RLDIR		=	-L/opt/vagrant/embedded/lib
RLINC		=	-I/opt/vagrant/embedded/include/readline
LIBFT		=	libft/libft.a
INC			=	minishell/includes
SRCSPATH	=	minishell/srcs
BUILT		=	$(SRCSPATH)/builtins
EXEC		=	$(SRCSPATH)/execution
LEX			=	$(SRCSPATH)/lex
SIG			=	$(SRCSPATH)/signals
UTILS		=	$(SRCSPATH)/utils

SRCS		=	$(SRCSPATH)/minishell.c

OBJS		=	$(SRCS:.c=.o)

$(LIBFT):
	@$(MAKE)	-C libft

%.o: %.c
	@$(CC) -I(INC) $(CFLAGS) -c $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJS)	$(LIBFT)
	@$(CC) $(CFLAGS) $(RLDIR) $(RLINC) $(OBJS) -o $@ $(RLFLAGS)

clean	:
	@$(MAKE)	-C libft clean
	@rm -rf		$(OBJS)

fclean	:	clean
	@$(MAKE)	-C libft fclean
	@rm -rf		$(NAME)

re		:	fclean	all

.PHONY:	all clean fclean re