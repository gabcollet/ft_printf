/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:11:25 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/10 15:05:49 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include "libft/ft_strlcpy.c"
# include "libft/ft_atoi.c"
# include "libft/ft_strlen.c"

typedef struct s_flags
{
	int	minus;
	int zero;
	int	precision;
	int	width;

}		t_flags;

#endif