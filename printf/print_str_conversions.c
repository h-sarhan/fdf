/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:50:37 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/01 12:43:53 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Prints a string conversion
// Handles the following flags
// 1. Minimum width
// 2. Left adjustment '-'
// 3. Precision
int	print_string_conversion(t_conversion *conv, char *val)
{
	int		num_printed;
	char	null_str[20];
	int		i;

	if (val == NULL)
	{
		ft_strlcpy(null_str, "(null)", 20);
		val = null_str;
	}
	calculate_padding(conv, &val);
	if (!conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	num_printed = conv->mw_padding;
	i = 0;
	while (val[i] != '\0' && (i < conv->precision_amount || !conv->precision))
	{
		ft_putchar_fd(val[i], STDOUT);
		i++;
		num_printed++;
	}
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

// Prints a character conversion
// Handles the following flags
// 1. Minimum width
// 2. Left adjustment '-'
int	print_char_conversion(t_conversion *conv, char val)
{
	int	num_printed;

	calculate_padding(conv, &val);
	if (!conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	num_printed = conv->mw_padding;
	ft_putchar_fd(val, STDOUT);
	num_printed += 1;
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}
