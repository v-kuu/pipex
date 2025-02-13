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

SOURCES_BONUS	= pipex_bonus.c \
				  file_handling_bonus.c \
				  command_handling_bonus.c \
				  execution_bonus.c

HEADERS			= pipex.h

HEADERS_BONUS	= pipex_bonus.h

OBJECTS			= $(SOURCES:.c=.o)

OBJECTS_BONUS	= $(SOURCES_BONUS:.c=.o)


%.o:			%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

%.o:			%.c $(HEADERS_BONUS)
	@$(CC) $(CFLAGS) -c $< -o $@

all: 			$(NAME)

$(NAME):		$(LIBFT) $(OBJECTS) $(HEADERS)
	@echo "Compiling pipex..."
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

bonus:			$(LIBFT) $(OBJECTS_BONUS) $(HEADERS_BONUS)
	@echo "Compiling bonuses..."
	@$(CC) $(CFLAGS) $(OBJECTS_BONUS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@make -C libft/ --no-print-directory

clean:
	@echo "Cleaning objects..."
	@$(RM) $(OBJECTS) $(OBJECTS_BONUS)
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
	norminette $(SOURCES) $(SOURCES_BONUS) $(HEADERS) $(HEADERS_BONUS) ./libft

.PHONY:			all clean fclean re fsanitize debug gprof norminette bonus
