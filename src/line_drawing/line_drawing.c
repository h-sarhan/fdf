/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:08:48 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/29 13:58:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


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

float	clamp_pixel(float p, char hv)
{
	if (p < 0)
		return 0;
	if (hv == 'h' && p >= SCREEN_W)
		p = SCREEN_W - 1;
	if (hv == 'v' && p >= SCREEN_H)
		p = SCREEN_H - 1;
	return p;
}

void	dda(t_fdf *fdf, float x1, float x2, float y1, float y2, int c1, int c2)
{
	float	dy;
	float	dx;
	float	c;

	x1 = clamp_pixel(x1, 'h');
	x2 = clamp_pixel(x2, 'h');
	y1 = clamp_pixel(y1, 'v');
	y2 = clamp_pixel(y2, 'v');
	dx = (x2 - x1);
	dy = (y2 - y1);
	if (fabs(dx) > fabs(dy))
		c = fabs(dx);
	else
		c = fabs(dy);
	dx /= c;
	dy /= c;
	int r = get_r(c1);
	int g = get_g(c1);
	int b = get_b(c1);
	int dr = (-r + get_r(c2)) / (float)c;
	int dg = (-g + get_g(c2)) / (float)c;
	int db = (-b + get_b(c2)) / (float)c;
	r <<= 16;
	g <<= 8;
	dr <<= 16;
	dg <<= 8;
	while (c > 0)
	{
		*(unsigned int*)(fdf->addr + (int)((int)y1 * fdf->line_size + (int)x1 * fdf->bpp)) = r | g | b;
		y1 += dy;
		x1 += dx;
		r += dr;
		g += dg;
		b += db;
		c--;
	}
}

// void bresenham(t_fdf *fdf, int x0, int x1, int y0, int y1, int color)
// {
//   int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
//   int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
//   int err = dx + dy, e2; /* error value e_xy */
 
//   for (;;){  /* loop */
// 	if (y0 >= 0 && x0 >= 0 && y0 < SCREEN_H && x0 < SCREEN_W)
// 	{
// 		*(unsigned int *)(fdf->addr + (int)((int)y0 * fdf->line_size + (int)x0 * fdf->bpp)) = color;
// 	}
//     if (x0 == x1 && y0 == y1) break;
//     e2 = 2 * err;
//     if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
//     if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
//   }
// }
