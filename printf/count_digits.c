/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:34:38 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/01 10:28:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Counts the number of digits in an integer including the negative sign
int	count_digits_int(int num)
{
	int	num_digits;

	num_digits = 0;
	if (num == 0)
		return (1);
	if (num == INT_MIN)
		return (11);
	if (num < 0)
	{
		num_digits += 1;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		num_digits++;
	}
	return (num_digits);
}

// Counts the number of digits in an unsigned integer
int	count_digits_unsigned(unsigned int num)
{
	int	num_digits;

	num_digits = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		num_digits++;
	}
	return (num_digits);
}

// Counts the number of hexadecimal digits in an unsigned long
// by traversing through it 4 bits at a time
// Skips trailing zeros
int	count_hex(unsigned long num)
{
	unsigned char	*bytes;
	unsigned char	hex_char;
	int				i;
	int				num_hex;

	if (num == 0)
		return (1);
	bytes = (unsigned char *) &num;
	i = 7;
	num_hex = 0;
	while (i >= 0)
	{
		hex_char = bytes[i] >> 4;
		if (hex_char != 0 || num_hex > 0)
			num_hex++;
		hex_char = bytes[i] & 0x0f;
		if (hex_char != 0 || num_hex > 0)
			num_hex++;
		i--;
	}
	return (num_hex);
}
