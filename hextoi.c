/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hextoi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:57:54 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 17:54:03 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

// Read a hexadecimal string and return an integer
unsigned int	hextoi(char *str)
{
	unsigned int	num;
	int				i;

	num = 0;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f')
		|| (str[i] >= 'A' && str[i] <= 'F'))
	{
		num *= 16;
		if (str[i] >= '0' && str[i] <= '9')
			num += str[i++] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			num += str[i++] - 'a' + 10;
		else
			num += str[i++] - 'A' + 10;
	}
	return (num);
}
