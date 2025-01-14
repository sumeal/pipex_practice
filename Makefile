# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 17:07:50 by muzz              #+#    #+#              #
#    Updated: 2025/01/14 18:12:26 by muzz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = main.c \
      pipex.c 

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Target to build the program
all: $(NAME)

# Linking the program with libft
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(LIBFT):
	make -C $(LIBFT_DIR)

# Target to clean object files
clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean

# Target to clean both the object files and the libft library
fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

# Include libft make rules
.PHONY: all clean fclean re
