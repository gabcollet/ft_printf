/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:39:40 by gcollet           #+#    #+#             */
/*   Updated: 2021/06/23 10:16:18 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* La fonction strlen() calcule la longueur de la chaîne de caractères s, sans 
compter l'octet nul « \0 » final. */
/* La fonction strlen() renvoie le nombre de caractères dans la chaîne s. */

#include "../includes/ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t			i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}
