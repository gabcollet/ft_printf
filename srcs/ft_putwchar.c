/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:16:17 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/29 14:29:53 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

unsigned int	get_header(wint_t c)
{
	if (c > 0x3FFFFFF)
		return (0xF1);
	if (c > 0xFFFF)
		return (0xF0);
	else if (c > 0x7FF)
		return (0xE0);
	else if (c > 0x7F)
		return (0xC0);
	else
		return (0x00);
}

unsigned int	get_mask(wint_t c)
{
	if (c > 0x3FFFFFF)
		return (0x03);
	if (c > 0xFFFF)
		return (0x07);
	else if (c > 0x7FF)
		return (0x0F);
	else if (c > 0x7F)
		return (0x1F);
	else
		return (0x00);
}

int	get_shift(wint_t c)
{
	if (c > 0x3FFFFFF)
		return (24);
	if (c > 0xFFFF)
		return (18);
	else if (c > 0x7FF)
		return (12);
	else if (c > 0x7F)
		return (6);
	else
		return (-1);
}

size_t	ft_wchar_size(wint_t c)
{
	if (c > 0x3FFFFFF)
		return (5);
	if (c > 0xFFFF)
		return (4);
	else if (c > 0x7FF)
		return (3);
	else if (c > 0x7F)
		return (2);
	else
		return (1);
}

int	ft_putwchar(wint_t c, int ret)
{
	unsigned int	header;
	unsigned int	mask;
	int				shift;

	header = get_header(c);
	mask = get_mask(c);
	shift = get_shift(c);
	if (ft_wchar_size(c) == 1)
		ret = ft_putchar((char)c, ret);
	else
	{
		ret = ft_putchar(header | (((c >> shift) & mask)), ret);
		shift -= 6;
	}
	while (shift >= 0)
	{
		ret = ft_putchar(0x80 | ((c >> shift) & 0x3F), ret);
		shift -= 6;
	}
	return (ret);
}
