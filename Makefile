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

FLAGS	= -Wextra -Werror -Wall

NAME	= pipex

HEADER = ./Includes
HDR = $(HEADER)/pipex.h

SOURCES	= check.c			\
		  pipex.c			\
		  pipex_utils.c		\
		  ft_split.c		\
		  files.c			\
		  error.c			\
		  main.c			\
		  here_doc.c		\
		  get_next_line.c	\
		  get_next_line_utils.c	

SRCS = $(addprefix ./Sources/, $(SOURCES))

OBJECTS =	$(SOURCES:.c=.o)
OBJS = $(addprefix ./Objects/, $(OBJECTS))

DEPENDENCIES = $(SOURCES:.c=.d)
DEPS = $(addprefix ./Objects/, $(DEPENDENCIES))

all:	 $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

RM = rm -rf

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(RM) $(NAME) $(DEPS)

re:	fclean all

/Objects/%.o : ./Sources%.c $(HDR)
				mkdir -p Objects
				$(CC) $(FLAGS) -MMD -I $(HEADER) -o $@ -c $<


.PHONY: all clean fclean re
