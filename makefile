# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:17:34 by tabadawi          #+#    #+#              #
#    Updated: 2024/07/08 12:29:08 by tabadawi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
CFLAGS		+=	-fsanitize=address -g3

# the following flagsg are to be used on 42 computers
RLFLAGS		=	-lreadline -lhistory
RLDIR		=	-L/opt/vagrant/embedded/lib
RLINC		=	-I/opt/vagrant/embedded/include/readline/readline.h


# and the following flags are to be used on personal computers
# RLDIR += -L/usr/local/opt/readline/lib
# RLINC += -I/usr/local/opt/readline/include
# RLFLAGS = -lreadline -lhistory

GREY		= $'\x1b[30m
RED			= $'\x1b[31m
GREEN		= $'\x1b[32m
YELLOW		= $'\x1b[33m
BLUE		= $'\x1b[34m
PURPLE		= $'\x1b[35m
CYAN		= $'\x1b[36m
WHITE		= $'\x1b[37m


define HEADER
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▓▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▓▒▒▒▒▒▒▒▓█▓▓▓▓▓▓▓▒░░░░░░░▒▒▒▓▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▓▒▒▒▒▒░░░░▒█▓▒░░░░░░░░▒▓▒░░░▒▒▒▒▒░░▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒░░░░░░░░░░░░▒▒▓▓▓▒▒▓▓▓▓▒░░▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒█▒░░░░░▒▓▓▒░░░░░▓░░░░░░░░▒█▒░░░▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░▒▓▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒█░░░▒▓░░▒█▓▓░░░░▒░▒▓▓▓▒░░░░█▒▒▒░░▒▒▒▒▒▒▒░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒▒▒▓▒░░▒▓▓████▓▒░░░▓░▒██▒▓░░░░▓▒▒▒▒▒▒▒▒▓▒▒▒▒▒░░░░░░░░░░░░
░░░░░░░░░░░░░▒▓▒▒▒▒▒▒▒▒▒▒▒▓▒▒▒▒▒▒▒▒░░▒▒▒░▓▓▓▓▓▓▒░░░▒▓▓██▒▒▓░░░░▓▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒░░░░░░░░░░
░░░░░░░░░░░░▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▓▓▓▓▒▒▒▒▒▒▒░▒▒▒░▒▒▒░░░░▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒░░░░░░░░
░░░░░░░░░░▒▓▒▒▒▒▒▒▒▒▒▒▓▒▒▒▒▒▒▓█▓▓▓▓▒▒▒▒▒▒▒▒▒░░░▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░
░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓██▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░░░░░
░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▓░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░░░░
░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓█▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░░░
░░░░░░▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▓░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░░
░░░░░░▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓███▓░░░░░░░░░░░░░░░░░░░░░░░░░░░▓█▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒░░
░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████▓▒░░░░░░░░░░░░░░░░░░░░░░░▒██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░
░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████████▓▓░░░░░░░░░░░░░░░░░░▒▓███▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░
░░░░░▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓█████████░▒▒█▓▓▓▒▒▒▒▒▒▓▓██▓▓████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒░
░░░░░▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█████████▒▒▓████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░
░░░░░▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓████████▒▒████████████████████▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░
░░░░░▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒███████▓▒█████████████████████▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░
░░░░░▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒██████▒▒████████████████▓▓▓██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░
░░░░░▒▒▒░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▓█████▒▒██████████▓▓███████▓▓█▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░
░░░░░░▓▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░▓███▓▒▓███████████▓▓▓▓█████████▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░
░░░░░░▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░▒██▒▒▓██████████████▓▓▓█████████▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓░░░
░░░░░░░▓▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░▒▒▒▒▒█████████████████▓████████▓▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒░░░
░░░░░░░░▓▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░▒▒▒▒▓▓▓▓██████████████████████▒▒▒▒▒▒▒▒▒▒▒▒▓▒░░░░
░░░░░░░░░▓▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░▒▒▒░░░░▒▒▒▒░▒▓████████████████████▒▒▒▒▒▒▒▒▒▒▒▓▒░░░░░
░░░░░░░░░░▓▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░░▒▒▒▒▓██▓▓▓██████████████▒▒▒▒▒▒▒▒▒▒▓▒░░░░░░
░░░░░░░░░░░▒▒▒░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒░░░░░░░░░░░▒▒▒▒▒▒▓████████████▓▒▒▒▒▒▒▒▒▒▒░░░░░░░░
░░░░░░░░░░░░▒▓▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░▒▒░▒▒▒▒▒▒▒▓███████████▒▒▒▒▒▒▒▒▓▒░░░░░░░░░
░░░░░░░░░░░░░░▒▓▒▒░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░▒▒▒▒░▒▒▒▒▒▒▒▒▓████████▓▒▒▒▒▒▒▒▓▒░░░░░░░░░░░
░░░░░░░░░░░░░░░░▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▒▒▒▒▒▒▒▓▒░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒▒░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▒▒░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▓▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒░▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

endef
export HEADER

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
				$(UTILS)/freestuff.c $(LEX)/first_try.c $(SIG)/exit.c $(BUILT)/env.c \
				$(BUILT)/exit.c $(BUILT)/builtin_check.c $(BUILT)/pwd.c $(BUILT)/echo.c


OBJS		=	$(SRCS:.c=.o)

all		:	$(NAME)
			@echo ""
			@echo "$$HEADER"
			@echo "$(YELLOW)Created: $(words $(OBJS)) object file(s) for minishell or 𝓯𝓻𝓮𝓪𝓴𝔂shell"
			@echo "$(YELLOW)Created: $(NAME)$(RESET)"


$(LIBFT):
	@$(MAKE)	-C libft
	
$(NAME)	:	$(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(RLDIR) $(RLINC) $(OBJS) $(LIBFT)  -o $@ $(RLFLAGS)

%.o: %.c
	@$(CC) -I$(INC) $(CFLAGS) -c $< -o $@

clean	:
	@$(MAKE)	-C libft clean
	@rm -rf		$(OBJS)
	@echo ""
	@echo "${RED}$$HEADER"
	@echo "$(YELLOW)Removed: $(words $(OBJS)) object file(s) from minishell"

fclean	:	clean
	@$(MAKE)	-C libft fclean
	@rm -rf		$(NAME)
	@echo "$(YELLOW)Removed: $(NAME)$(RESET) no more 𝓯𝓻𝓮𝓪𝓴𝔂"


re		:	fclean	all

.PHONY:	all clean fclean re