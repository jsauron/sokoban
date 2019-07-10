# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile2                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsauron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/10 16:14:33 by jsauron           #+#    #+#              #
#    Updated: 2019/07/10 17:52:21 by jsauron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= sokoban
CC 			= clang
CFLAGS 		= -Wall -Wextra -Werror -g -O3 #-fsanitize=address

ID_UN 		= $(shell id -un)
SRC_PATH 	= srcs/
OBJ_PATH 	= objs/

WHITE       = "\\033[0m"
CYAN        = "\\033[36m"
GREEN       = "\\033[32m"

SDL_NUM= $(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2/ | tail -1)
TTF_NUM= $(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/ | tail -1)
IMG_NUM= $(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2_image/ | tail -1)
MIX_NUM= $(shell ls /Users/$(ID_UN)/.brew/Cellar/sdl2_mixer/ | tail -1)

INC_PATH+= /Users/$(ID_UN)/.brew/Cellar/sdl2/$(SDL_NUM)/include/ \
		   /Users/$(ID_UN)/.brew/Cellar/sdl2/$(SDL_NUM)/include/SDL2/ \
			/Users/$(ID_UN)/.brew/Cellar/sdl2_ttf/$(TTF_NUM)/include/ \
			/Users/$(ID_UN)/.brew/Cellar/sdl2_image/$(IMG_NUM)/include/ \

SRC_NAME 	= main.c \
				jeu.c \
				files.c \
				editor.c

OBJ_NAME = $(patsubst %.c, $(OBJ_PATH)%.o, $(SRC_NAME))
LSDL2 	 = -L/Users/$(ID_UN)/.brew/lib/ -lSDL2 -lSDL2_ttf -lSDL2_image

vpath %.c srcs/ 
vpath %.h includes/

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(OBJ_NAME)
INC = $(addprefix -I, $(INC_PATH))

all: $(NAME)

$(OBJ) : | $(OBJ_PATH)

$(OBJ_PATH) :
		mkdir objs

$(NAME):  $(OBJ_PATH) $(OBJ_NAME)
			printf "$(CYAN)[WAIT]$(WHITE) Compiling into %-50s\r" $(NAME)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC) $(LSDL2)
			printf "$(GREEN)[OK]$(WHITE) %s has been well compiled\n" $(NAME)

$(OBJ_NAME): ./$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -I includes/ -c $< -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_PATH) Makefile
		printf "$(CYAN)[WAIT]$(WHITE) Compiling into .o %-50s\r" $@
		$(CC) $(CFLAGS) $(INC) -o  -c $<

clean:
			rm -rf $(OBJ_PATH)
			printf "$(GREEN)[OK]$(WHITE) Clean done\n"

fclean: clean
			rm -f $(NAME)
			printf "$(GREEN)[OK]$(WHITE) Fclean done\n"

re: fclean all
	@$(MAKE)

.PHONY: all re clean fclean
