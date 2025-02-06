# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/20 12:42:28 by vkuusela          #+#    #+#              #
#    Updated: 2025/01/23 13:23:37 by vkuusela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

		### BASICS ###

NAME 			= pipex
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -I.
RM 				= rm -rf

		### LIBRARIES ###

LIBFT			= libft/libft.a

		### SOURCE ###

SOURCES			= pipex.c \
				  file_handling.c \
				  command_handling.c \
				  execution.c

HEADERS			= pipex.h

OBJECTS			= $(SOURCES:.c=.o)

%.o:			%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

all: 			$(NAME)

$(NAME):		$(LIBFT) $(OBJECTS)
	@echo "Compiling pipex..."
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@make -C libft/ --no-print-directory

clean:
	@echo "Cleaning objects..."
	@$(RM) $(OBJECTS)
	@(cd libft/ && make clean)

fclean:			clean
	@echo "Full clean..."
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re:				fclean all

debug:			CFLAGS += -g
debug:			re

fsanitize:		CFLAGS += -g -fsanitize=address
fsanitize:		re

gprof:			CFLAGS += -g -pg
gprof:			re

norminette:
	norminette $(SOURCES) $(HEADERS) ./libft

.PHONY:			all clean fclean re fsanitize debug gprof norminette
