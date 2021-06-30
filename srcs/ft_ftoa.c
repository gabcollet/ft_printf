/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 12:20:36 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/30 17:13:25 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	reverse(char* str, int len)
{
    int i;
	int j;
	int temp;
	
	i = 0; 
	j = len - 1;
    while (i < j)
	{
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int	ft_intToStr(long x, char str[], int d)
{
    int i;

	i = 0;
    if (x == 0)
        str[i++] = '0';
    if (x == LLONG_MIN)
    {
        x = x / 10;
        x = -x;
        str[i++] = '8';
    }
    while (x)
	{
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while (i < d)
        str[i++] = '0';
    reverse(str, i);
    str[i] = '\0';
    return (i);
}

char	*ft_ftoa(double n, int fdigit, t_s s)
{
    long ipart;
	double fpart;
	int i;
	
	s.ptr = (char *)malloc(sizeof(char) * (3 + DBL_MANT_DIG - DBL_MIN_EXP));
	ipart = (long)n;
    fpart = n - ipart;
    i = ft_intToStr(ipart, s.ptr, 0);
    if (fdigit != 0) 
	{
        s.ptr[i] = '.';
        if (fpart == ULLONG_MAX)
            fpart = 0;
        if (fpart != 0)
        {
            while (fdigit != 0)
            {
                fpart *= 10;
                fdigit--;
            }
        }
        ft_intToStr((int)fpart, s.ptr + i + 1, fdigit);
    }
	return (s.ptr);
}
