# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsauron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/01 18:30:18 by jsauron           #+#    #+#              #
#    Updated: 2019/07/10 15:44:08 by jsauron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = sokoban


SRCS_DIR = srcs/


SRC = srcs/main.c \
	  srcs/jeu.c \
	  srcs/files.c \
	  srcs/editor.c 

OBJS = $(SRC:.c=.o)

INCLUDES = includes/

DEBUG = -g -fsanitize=address

DONE = "\033[35m LS READY \033[0m"

all: $(NAME)

$(NAME): $(OBJS)
	@gcc -Wall -Wextra -Werror -o $(NAME) $(OBJS) -I $(INCLUDES)  $(DEBUG)
	@echo $(DONE)

%.o: %.c $(INCLUDES)sokoban.h
	@gcc -Wall -Wextra -Werror -o $@ -c $<


clean:
	@rm -f $(OBJS) 

fclean:
	@rm -f $(NAME) 

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re
