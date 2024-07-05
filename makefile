# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:17:34 by tabadawi          #+#    #+#              #
#    Updated: 2024/07/05 21:18:03 by tarekkkk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
CFLAGS		+=	-fsanitize=address -g3

# the following flagsg are to be used on 42 computers
# RLFLAGS		=	-lreadline -lhistory
# RLDIR		=	-L/opt/vagrant/embedded/lib
# RLINC		=	-I/opt/vagrant/embedded/include/readline/readline.h


# and the following flags are to be used on personal computers
RLDIR += -L/usr/local/opt/readline/lib
RLINC += -I/usr/local/opt/readline/include
RLFLAGS = -lreadline -lhistory



LIBFT		=	libft/libft.a
INC			=	mini_shell/includes
SRCSPATH	=	mini_shell/srcs
BUILT		=	$(SRCSPATH)/builtins
EXEC		=	$(SRCSPATH)/execution
LEX			=	$(SRCSPATH)/lex
SIG			=	$(SRCSPATH)/signals
UTILS		=	$(SRCSPATH)/utils
ENV			=	$(SRCSPATH)/environ


SRCS		=	$(SRCSPATH)/minishell.c $(UTILS)/ft_strjoin2.c $(ENV)/env_utils.c \
				$(UTILS)/freestuff.c $(LEX)/first_try.c $(SIG)/exit.c


OBJS		=	$(SRCS:.c=.o)

all		:	$(NAME)

$(LIBFT):
	@$(MAKE)	-C libft
	
$(NAME)	:	$(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(RLDIR) $(RLINC) $(OBJS) $(LIBFT)  -o $@ $(RLFLAGS)

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