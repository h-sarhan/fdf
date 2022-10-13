/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:38:19 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/01 10:28:15 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Prefixes `0x` before printing the hex value of a pointer
void	print_hex_pointer(void *pointer)
{
	ft_putstr_fd("0x", STDOUT);
	if (pointer == NULL)
	{
		ft_putchar_fd('0', STDOUT);
	}
	print_hex((unsigned long) pointer, 'x');
}

// Prints the hex value of an unsigned int
void	print_hex_int(unsigned int num, char hex_type)
{
	if (num == 0)
	{
		ft_putchar_fd('0', STDOUT);
		return ;
	}
	print_hex(num, hex_type);
}

// Prints a character `c` n times
void	print_n_chars(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putchar_fd(c, STDOUT);
		i++;
	}
}

// Returns the larger of two ints
int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
