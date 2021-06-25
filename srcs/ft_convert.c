/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 12:18:09 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/25 12:18:29 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_convert(unsigned long num, int base, int maj)
{
	static char	val[17];
	static char	buffer[50];
	char		*ptr;

	ft_strlcpy(val, "0123456789abcdef", 17);
	if (maj == 1)
		ft_strlcpy(val, "0123456789ABCDEF", 17);
	ptr = &buffer[49];
	*ptr = '\0';
	*--ptr = val[num % base];
	num /= base;
	while (num != 0)
	{
		*--ptr = val[num % base];
		num /= base;
	}
	return (ptr);
}
