# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:17:34 by tabadawi          #+#    #+#              #
#    Updated: 2024/06/10 19:58:35 by tabadawi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
RLFLAGS		=	-lreadline -lhistory
RLDIR		=	-L/opt/vagrant/embedded/lib
RLINC		=	-I/opt/vagrant/embedded/include/readline
LIBFT		=	libft/libft.a
INC			=	mini_shell/includes
SRCSPATH	=	mini_shell/srcs
BUILT		=	$(SRCSPATH)/builtins
EXEC		=	$(SRCSPATH)/execution
LEX			=	$(SRCSPATH)/lex
SIG			=	$(SRCSPATH)/signals
UTILS		=	$(SRCSPATH)/utils
SRCS		=	$(SRCSPATH)/minishell.c
OBJS		=	$(SRCS:.c=.o)

all		:	$(NAME)

$(LIBFT):
	@$(MAKE)	-C libft
	
$(NAME)	:	$(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(RLDIR) $(RLINC)  $(LIBFT) $(OBJS) -o $@ $(RLFLAGS)

%.o: %.c
	@$(CC) -I$(INC) $(CFLAGS) -c $< -o $@

clean	:
	@$(MAKE)	-C libft clean
	@rm -rf		$(OBJS)

fclean	:	clean
	@$(MAKE)	-C libft fclean
	@rm -rf		$(NAME)

re		:	fclean	all

.PHONY:	all clean fclean re