# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/11 12:58:26 by gcollet           #+#    #+#              #
#    Updated: 2021/06/23 10:41:01 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a
SRCS 	= srcs/ft_atoi.c srcs/ft_strlcpy.c srcs/ft_strlen.c srcs/ft_printf.c
OBJS 	= ${SRCS:.c=.o}
HEADER	= includes/ft_printf.h

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror

.c.o:		%.o : %.c
					${CC} ${CFLAGS} -I ${HEADER} -c $< -o $(<:.c=.o)

$(NAME):	${OBJS}
					ar rc ${NAME} ${OBJS}

all: 		${NAME}

clean:
					rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re bonus