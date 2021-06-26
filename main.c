/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 10:19:07 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/25 17:16:41 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include <limits.h>

/* #include "../srcs/ft_atoi.c"
#include "../srcs/ft_strlcpy.c"
#include "../srcs/ft_strlen.c" */

int main()
{
	int ret = 0;
	int retp = 0;
	
	ret = ft_printf(" %lc ", u'ƀ');
	printf("\n============================================================\n");
	retp = printf(" %lc ", u'ƀ');
	printf("\n#char imprimé ft_printf: %d\n", ret);
	printf("#char imprimé printf: %d\n", retp);
	return 0;
}

/* int main()
{
	int		a = -4;
	int		b = 0;
	char	c = 'a';
	int		d = 2147483647;
	int		e = -2147483648;
	int		f = 42;
	int		g = 25;
	int		h = 4200;
	int		i = 8;
	int		j = -12;
	int		k = 123456789;
	int		l = 0;
	int		m = -12345678;
	char	*n = "abcdefghijklmnop";
	char	*o = "-a";
	char	*p = "-12";
	char	*q = "0";
	char	*r = "%%";
	char	*s = "-2147483648";
	char	*t = "0x12345678";
	char	*u = "-0";

	ft_printf("%u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X, %u, %x, %X", i, i, i, j, j, j, k, k, k, l, l, l, m, m, m, c, c, c, d, d, d, e, e, e);
} */
