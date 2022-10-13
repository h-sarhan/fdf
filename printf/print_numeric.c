/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numeric_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:10:58 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/01 10:28:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Converts a decimal number from 0 to 15 to its hexadecimal equivalent
// Example: 
// 10 -> 'a' or 'A'
// 11 -> 'b' or 'B'
// 15 -> 'f' or 'F'
char	dec_to_hex(unsigned char dec, char hex_type)
{
	if (dec > 9)
	{
		if (hex_type == 'X')
			return (dec + 'A' - 10);
		else
			return (dec + 'a' - 10);
	}
	return (dec + '0');
}

// Prints an unsigned long in hexadecimal form by
// traversing through the number 4 bits at a time
// Skips trailing zeroes
void	print_hex(unsigned long num, char hex_type)
{
	unsigned char	*bytes;
	unsigned char	hex_char;
	int				i;
	t_bool			start;

	bytes = (unsigned char *) &num;
	i = 7;
	start = FALSE;
	while (i >= 0)
	{
		hex_char = bytes[i] >> 4;
		if (hex_char != 0 || start == TRUE)
		{
			ft_putchar_fd(dec_to_hex(hex_char, hex_type), STDOUT);
			start = TRUE;
		}
		hex_char = bytes[i] & 0x0f;
		if (hex_char != 0 || start == TRUE)
		{
			ft_putchar_fd(dec_to_hex(hex_char, hex_type), STDOUT);
			start = TRUE;
		}
		i--;
	}
}

// Prints an unsigned int
void	print_unsigned_int(unsigned int num)
{
	if (num < 10)
	{
		ft_putchar_fd(num + '0', 1);
	}
	else
	{
		ft_putnbr_fd(num / 10, 1);
		ft_putchar_fd(num % 10 + '0', 1);
	}
}

// Prints a signed integer with optional zero padding
void	print_int(int num, int padding)
{
	if (num == INT_MIN)
	{
		ft_putchar_fd('-', STDOUT);
		print_n_chars('0', padding);
		ft_putstr_fd("2147483648", STDOUT);
		return ;
	}
	if (num < 0)
	{
		ft_putchar_fd('-', STDOUT);
		num *= -1;
	}
	print_n_chars('0', padding);
	ft_putnbr_fd(num, STDOUT);
}
