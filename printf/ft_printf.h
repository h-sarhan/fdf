/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:39:42 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/25 20:38:29 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdarg.h>

# define STDOUT 1
# define TRUE 1
# define FALSE 0

typedef int						t_bool;
typedef struct s_conversion		t_conversion;
struct							s_conversion {
	char	type;
	int		min_width;
	t_bool	pad_zeros;
	t_bool	precision;
	int		precision_amount;
	t_bool	alt_form;
	t_bool	space;
	t_bool	sign;
	t_bool	pad_right;
	int		mw_padding;
	int		pr_padding;
};

// print_utils.c
void			print_hex_pointer(void *pointer);
void			print_hex_int(unsigned int num, char hex_type);
void			print_n_chars(char c, int n);
int				max(int a, int b);

// print_numeric.c
void			print_int(int num, int padding);
void			print_unsigned_int(unsigned int num);
void			print_hex(unsigned long num, char hex_type);

// count_digits.c
int				count_digits_int(int num);
int				count_digits_unsigned(unsigned int num);
int				count_hex(unsigned long num);

// conversion.c
t_conversion	*new_conversion(char *fmt);
void			parse_conversion_string(char *fmt, t_conversion *conv);
void			calculate_padding(t_conversion *conv, void *val);
int				count_initial_chars(t_conversion *conv, void *val);
int				print_conversion(t_conversion *conv, va_list args);

// print_num_conversions.c
int				print_hex_conversion(t_conversion *conv, unsigned int val);
int				print_pointer_conversion(t_conversion *conv, void *val);
int				print_int_conversion(t_conversion *conv, int val);
int				print_uint_conversion(t_conversion *conv, unsigned int val);

// print_str_conversions.c
int				print_char_conversion(t_conversion *conv, char val);
int				print_string_conversion(t_conversion *conv, char *val);

// ft_printf.c
int				ft_printf(const char *fmt, ...);
#endif
