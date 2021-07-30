# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/11 12:58:26 by gcollet           #+#    #+#              #
#    Updated: 2021/07/12 11:03:31 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a
SRCS 	= srcs/ft_atoi.c srcs/ft_strlcpy.c srcs/ft_strlen.c srcs/ft_printf.c\
		srcs/ft_check_flags.c srcs/ft_convert.c srcs/ft_format.c\
		srcs/ft_print_dori.c srcs/ft_print_dori1.c srcs/ft_print_p.c\
		srcs/ft_print_s.c srcs/ft_print_text.c srcs/ft_print_uint.c\
		srcs/ft_putchar.c srcs/ft_putstr.c srcs/ft_print_c.c\
		srcs/ft_check_flags_bonus.c srcs/ft_print_wc.c srcs/ft_putwchar.c\
		srcs/ft_print_ws.c srcs/ft_print_f.c srcs/ft_print_f1.c srcs/ft_ftoa.c
OBJS 	= ${SRCS:.c=.o}
SRCS_B	= 
OBJS_B	= ${SRCS_B:.c=.o}
HEADER	= includes/

CC 		= gcc
CFLAGS 	= -g -Wall -Wextra -Werror

.c.o:		%.o : %.c
					${CC} ${CFLAGS} -I ${HEADER} -c $< -o $(<:.c=.o)

$(NAME):	${OBJS}
					ar rc ${NAME} ${OBJS}

all: 		${NAME}

bonus:		${OBJS} ${OBJS_B}
					ar rc ${NAME} ${OBJS} ${OBJS_B}

clean:
					rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re bonus
