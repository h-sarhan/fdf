/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 09:32:49 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/25 20:43:13 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Extracts a conversion string (e.g. "%-100.45d") from a format string
// This function also increments the index to the format string
t_conversion	*extract_conversion(const char *fmt, int conv_start, size_t *i)
{
	int				conv_end;
	char			*conv_str;
	t_conversion	*conv;

	conv_end = conv_start;
	while (ft_strchr("%diuxXcsp", fmt[conv_end]) == NULL)
		conv_end++;
	*i = conv_end;
	conv_str = ft_substr(fmt, conv_start, conv_end - conv_start + 1);
	conv = new_conversion(conv_str);
	free(conv_str);
	return (conv);
}

// Printf
int	ft_printf(const char *fmt, ...)
{
	size_t			i;
	t_conversion	*conv;
	va_list			args;
	int				chars_printed;

	i = 0;
	chars_printed = 0;
	va_start(args, fmt);
	while (i < ft_strlen(fmt))
	{
		if (fmt[i] == '%')
		{
			conv = extract_conversion(fmt, i + 1, &i);
			chars_printed += print_conversion(conv, args);
			free(conv);
		}
		else
		{
			ft_putchar_fd(fmt[i], STDOUT);
			chars_printed++;
		}
		i++;
	}
	va_end(args);
	return (chars_printed);
}
