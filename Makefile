# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/11 12:58:26 by gcollet           #+#    #+#              #
#    Updated: 2021/06/25 12:23:47 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a
SRCS 	= srcs/ft_atoi.c srcs/ft_strlcpy.c srcs/ft_strlen.c srcs/ft_printf.c\
		srcs/ft_check.c srcs/ft_convert.c srcs/ft_format.c srcs/ft_print_c.c\
		srcs/ft_print_dori.c srcs/ft_print_dori1.c srcs/ft_print_p.c\
		srcs/ft_print_s.c srcs/ft_print_text.c srcs/ft_print_uint.c\
		srcs/ft_putchar.c srcs/ft_putstr.c
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