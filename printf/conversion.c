/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 00:21:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/01 13:09:08 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Creates and initialises a new conversion struct
t_conversion	*new_conversion(char *fmt)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	if (conv == NULL)
		return (NULL);
	conv->type = fmt[ft_strlen(fmt) - 1];
	conv->precision = ft_strchr(fmt, '.') != NULL;
	conv->alt_form = ft_strchr(fmt, '#') != NULL;
	conv->space = ft_strchr(fmt, ' ') != NULL;
	conv->sign = ft_strchr(fmt, '+') != NULL;
	conv->pad_right = ft_strchr(fmt, '-') != NULL;
	conv->pad_zeros = FALSE;
	conv->min_width = 0;
	conv->precision_amount = 0;
	parse_conversion_string(fmt, conv);
	conv->mw_padding = 0;
	conv->pr_padding = 0;
	return (conv);
}

// Parses a conversion string to figure out the precision and min_width amounts
void	parse_conversion_string(char *fmt, t_conversion *conv)
{
	int	i;

	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '0')
		{
			conv->pad_zeros = TRUE;
			i++;
		}
		else if (fmt[i] == '.')
			break ;
		else if (ft_isdigit(fmt[i]))
		{
			conv->min_width = ft_atoi(&fmt[i]);
			while (ft_isdigit(fmt[i]) && fmt[i] != '\0')
				i++;
			if (fmt[i] == '\0' || conv->precision)
				break ;
		}
		else
			i++;
	}
	if (conv->precision)
		conv->precision_amount = ft_atoi(ft_strchr(fmt, '.') + 1);
}

// Calculates the required additional padding based on a conversion
// and the value being printed.
// The calculation is based on the min width amount, precision amount
// conversion type, number of characters in the value, and the space/sign flags
void	calculate_padding(t_conversion *conv, void *val)
{	
	int	init_chrs;

	init_chrs = count_initial_chars(conv, val);
	if (ft_strchr("xXudi", conv->type) != NULL && conv->precision)
	{
		if (ft_strchr("di", conv->type) != NULL && *(int *) val < 0
			&& conv->precision_amount > init_chrs - 1)
			conv->pr_padding = max(conv->precision_amount - (init_chrs - 1), 0);
		else
			conv->pr_padding = max(conv->precision_amount - init_chrs, 0);
	}
	if (conv->type == 's' && conv->precision)
	{
		if (init_chrs > conv->precision_amount)
			init_chrs = conv->precision_amount;
		conv->mw_padding = max(conv->min_width - init_chrs, 0);
	}
	else if (conv->min_width > init_chrs + conv->pr_padding)
		conv->mw_padding = max(conv->min_width - conv->pr_padding
				- init_chrs, 0);
	if (ft_strchr("xX", conv->type) != NULL && conv->alt_form)
		conv->mw_padding = max(conv->mw_padding - 2, 0);
	if (ft_strchr("di", conv->type) != NULL
		&& (conv->space || conv->sign) && *(int *) val >= 0)
		conv->mw_padding = max(conv->mw_padding - 1, 0);
}

// Counts the the characters to be printed for a value without 
// extra padding/flags
int	count_initial_chars(t_conversion *conv, void *val)
{
	int	init_chrs;

	if (conv->type == 'x' || conv->type == 'X')
		init_chrs = count_hex(*(unsigned int *) val);
	else if (conv->type == 'u')
		init_chrs = count_digits_unsigned(*(unsigned int *) val);
	else if (conv->type == 'p')
		init_chrs = count_hex(*(unsigned long *) val) + 2;
	else if (conv->type == 's')
		init_chrs = ft_strlen(*(char **) val);
	else if (conv->type == 'c' || conv->type == '%')
		init_chrs = 1;
	else
		init_chrs = count_digits_int(*(int *) val);
	if (ft_strchr("iudxX", conv->type) != NULL
		&& *(int *) val == 0
		&& conv->precision
		&& conv->precision_amount == 0)
		init_chrs = 0;
	return (init_chrs);
}

// Prints a conversion
// Handles the following conversions
// 1. Hexadecimal 'x' or 'X'
// 2. Unsigned int 'u'
// 3. Void Pointer 'p'
// 4. String 's'
// 5. Character 'c'
// 6. Percent '%'
// 7. Integer 'd' or 'i'
int	print_conversion(t_conversion *conv, va_list args)
{
	if (conv->type == 'x' || conv->type == 'X')
		return (print_hex_conversion(conv, va_arg(args, unsigned int)));
	else if (conv->type == 'u')
		return (print_uint_conversion(conv, va_arg(args, unsigned int)));
	else if (conv->type == 'p')
		return (print_pointer_conversion(conv, va_arg(args, void *)) + 2);
	else if (conv->type == 's')
		return (print_string_conversion(conv, va_arg(args, char *)));
	else if (conv->type == 'c')
		return (print_char_conversion(conv, (char) va_arg(args, int)));
	else if (conv->type == '%')
		return (print_char_conversion(conv, '%'));
	else if (conv->type == 'd' || conv->type == 'i')
		return (print_int_conversion(conv, va_arg(args, int)));
	else
		return (-1);
}
