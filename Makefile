# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/03 10:11:11 by abin-moh          #+#    #+#              #
#    Updated: 2025/02/04 12:28:43 by abin-moh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = main.c              \
      pipex.c             \
      exec_child_helper.c \
	  pipex_helper.c      \
      ft_memcpy.c         \
      ft_printf.c         \
      ft_putchar.c        \
      ft_putnbr.c         \
      ft_putnbr_hex_lower.c \
      ft_putnbr_hex_upper.c \
      ft_putnbr_unsigned.c \
      ft_putptr.c         \
      ft_putstr.c         \
      ft_split.c          \
      ft_strchr.c         \
      ft_strdup.c         \
      ft_strjoin.c        \
      ft_strlen.c         \
      ft_strncmp.c        \
      ft_substr.c         \
      ft_strnstr.c        

OBJ = $(SRC:.c=.o)

%.o: %.c pipex.h ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
