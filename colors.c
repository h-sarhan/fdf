/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 19:16:14 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 17:45:20 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Create a color
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// Get the transparency of a color
int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

// Get the red part of a color
int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

// Get the green part of a color
int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

// Get the blue part of a color
int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
