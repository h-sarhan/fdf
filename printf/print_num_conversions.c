/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:45:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/01 12:46:00 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Prints a hexadecimal conversion 'x' or 'X'
// Handles the following flags
// 1. Minimum width
// 2. Left adjustment '-'
// 3. Zero padding
// 4. Alt form '#'
// 5. Precision
int	print_hex_conversion(t_conversion *conv, unsigned int val)
{
	int	num_printed;

	num_printed = count_hex(val);
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding + conv->pr_padding;
	if (!conv->pad_right && (!conv->pad_zeros || conv->precision))
		print_n_chars(' ', conv->mw_padding);
	if (conv->alt_form && val != 0)
	{
		num_printed += 2;
		ft_putchar_fd('0', STDOUT);
		ft_putchar_fd(conv->type, STDOUT);
	}
	if (conv->pad_zeros && !conv->precision && !conv->pad_right)
		print_n_chars('0', conv->mw_padding);
	if (conv->precision)
		print_n_chars('0', conv->pr_padding);
	if (val == 0 && conv->precision && conv->precision_amount == 0)
		num_printed--;
	else
		print_hex_int(val, conv->type);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

// Prints an unsigned int conversion 'u'
// Handles the following flags
// 1. Minimum width
// 2. Left adjustment '-'
// 3. Zero padding
// 4. Precision
int	print_uint_conversion(t_conversion *conv, unsigned int val)
{
	int	num_printed;

	num_printed = count_digits_unsigned(val);
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding + conv->pr_padding;
	if (!conv->pad_right && (!conv->pad_zeros || conv->precision))
		print_n_chars(' ', conv->mw_padding);
	if (conv->pad_zeros && !conv->precision && !conv->pad_right)
		print_n_chars('0', conv->mw_padding);
	if (conv->precision)
		print_n_chars('0', conv->pr_padding);
	if (val == 0 && conv->precision && conv->precision_amount == 0)
		num_printed--;
	else
		print_unsigned_int(val);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

// Prints a pointer conversion 'p'
// Handles the following flags
// 1. Minimum width
// 2. Left adjustment '-'
int	print_pointer_conversion(t_conversion *conv, void *val)
{
	int	num_printed;

	num_printed = count_hex((unsigned long)val);
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding;
	if (!conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	print_hex_pointer(val);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}

// Prints an integer conversion 'd' or 'i'
// Handles the following flags
// 1. Minimum width
// 2. Space ' '
// 3. Sign '+'
// 4. Left adjustment '-'
// 5. Zero padding
// 6. Precision
int	print_int_conversion(t_conversion *conv, int val)
{
	int	num_printed;

	num_printed = count_digits_int(val);
	calculate_padding(conv, &val);
	num_printed += conv->mw_padding + conv->pr_padding;
	if ((conv->space || conv->sign) && val >= 0)
		num_printed++;
	if (!conv->pad_right && (!conv->pad_zeros || conv->precision))
		print_n_chars(' ', conv->mw_padding);
	if (conv->space && !conv->sign && val >= 0)
		ft_putchar_fd(' ', STDOUT);
	else if (conv->sign && val >= 0)
		ft_putchar_fd('+', STDOUT);
	if (val == 0 && conv->precision && conv->precision_amount == 0)
		num_printed--;
	else if (conv->pad_zeros && !conv->precision && !conv->pad_right)
		print_int(val, conv->mw_padding);
	else if (conv->precision)
		print_int(val, conv->pr_padding);
	else
		print_int(val, 0);
	if (conv->pad_right)
		print_n_chars(' ', conv->mw_padding);
	return (num_printed);
}
