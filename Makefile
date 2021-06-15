# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/11 12:58:26 by gcollet           #+#    #+#              #
#    Updated: 2021/06/15 12:14:12 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ./libft/libft.a
NAME 	= libftprintf.a
SRCS 	= ft_printf.c
OBJS 	= ${SRCS:.c=.o}
HEADER	= libft.h

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror

.c.o:		%.o : %.c
					${CC} ${CFLAGS} -I ${HEADER} -c $< -o $(<:.c=.o)

$(NAME):	${OBJS}
					$(MAKE) bonus -C ./libft
					cp libft/libft.a $(NAME)
					ar rc ${NAME} ${OBJS}

all: 		${NAME}

clean:
					rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re bonus