# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malancar <malancar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 15:09:38 by malancar          #+#    #+#              #
#    Updated: 2023/07/20 15:01:25 by malancar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= cc

CFLAGS	= -Wextra -Werror -Wall

NAME	= pipex

HEADER = pipex.h

SRC		= check.c			\
		  pipex.c			\
		  pipex_utils.c		\
		  ft_split.c		\
		  files.c			\
		  error.c			\
		  main.c			\
		  here_doc.c		\
		  get_next_line.c	\
		  get_next_line_utils.c	

OBJ =	$(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

RM	= rm -f

all:	 $(NAME)

$(NAME):	$(OBJ) $(HEADER)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:	%.c
	@$(CC) $(CFLAGS) -MMD -c  $< -o $@

clean:
	$(RM) $(OBJ) $(DEPS)

fclean: clean
	@$(RM) $(NAME) $(DEPS)

re:	fclean all

-include : $(DEPS)

.PHONY: all clean fclean re
