# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 16:40:18 by sleonard          #+#    #+#              #
#    Updated: 2019/12/26 14:00:22 by sleonard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#    PROJECT    #
NAME = sleonard.filler

#    DIRECTORIES    #
SRC_DIR = ./sources/
LIB_DIR = ./libft/
LIB_PRINTF = ./libft/ft_printf/
OBJ_DIR = ./obj/
SRC_INC_DIR = ./includes/
LIB_INC_DIR = ./libft/includes

#    FLAGS    #
CFLGS = -Wall -Wextra -Werror
LFLGS = -L$(LIB_PRINTF) -lftprintf -L$(LIB_DIR) -lft
CC = clang

#    LIBFT    #
LIBFT = $(LIB_DIR)/libft.a

#    SOURCES AND HEADERS    #
SRC_FILES = algo.c block_parsing.c error.c main.c map_parsing.c \
			map_processing.c parsing.c safe_malloc.c utils.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

#    INCLUDES    #
INCL = -I$(SRC_INC_DIR) -I$(LIB_INC_DIR)

#    RULES    #
.PHONY: all clean fclean re

all: update $(OBJ_DIR) $(NAME)

update:
	@git submodule init
	@git submodule update --merge --remote

-include: $(DEPS)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLGS) -c -o $@ $< $(INCL)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLGS) -o $(NAME) $(OBJS) $(INCL) $(LFLGS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all
