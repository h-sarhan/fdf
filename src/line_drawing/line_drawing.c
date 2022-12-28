/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:08:48 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/29 02:21:57 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	clamp(int color)
{
	if (color < 0)
		return 0;
	if (color > 255)
		return 255;
	return (color);
}

					// Create a color
int	create_rgb(int r, int g, int b)
{
	return (clamp(r) << 16 | clamp(g) << 8 | clamp(b));
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

int	color_mix(int c1, int c2, float mix)
{
	int		r;
	int		g;
	int		b;
	float	mix2;

	mix2 = 1 - mix;
	r = get_r(c1) * (mix) + get_r(c2) * (mix2);
	g = get_g(c1) * (mix) + get_g(c2) * (mix2);
	b = get_b(c1) * (mix) + get_b(c2) * (mix2);
	return (r << 16 | g << 8 | b);
}


// color = color_mix(pts[0]->color, pts[1]->color,
// 					(float)(xy[0] - pts[0]->x) / (pts[1]->x - pts[0]->x));

void	dda(t_fdf *fdf, float x1, float x2, float y1, float y2, int c1, int c2)
{
	float	dy;
	float	dx;
	float	c;
	int		i;

	dx = (x2 - x1);
	dy = (y2 - y1);
	if (fabs(dx) > fabs(dy))
		c = fabs(dx);
	else
		c = fabs(dy);
	i = 0;
	dx /= c;
	dy /= c;
	int r1 = get_r(c1);
	float dr1 = r1 / (float)c;
	int g1 = get_g(c1);
	float dg1 = g1 / (float)c;
	int b1 = get_b(c1);
	float db1 = b1 / (float)c;
	int r2 = get_r(c2);
	float dr2 = r2 / (float)c;
	int g2 = get_g(c2);
	float dg2 = g2 / (float)c;
	int b2 = get_b(c2);
	float db2 = b2 / (float)c;
	while (i <= c)
	{
		if (y1 >= 0 && x1 >= 0 && y1 < SCREEN_H && x1 < SCREEN_W)
			*(unsigned int*)(fdf->addr + (int)((int)y1 * fdf->line_size + (int)x1 * fdf->bpp)) = create_rgb(r1, g1, b1);
		y1 += dy;
		x1 += dx;
		r1 = r1 - dr1 + dr2;
		g1 = g1 - dg1 + dg2;
		b1 = b1 - db1 + db2;
		i++;
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
