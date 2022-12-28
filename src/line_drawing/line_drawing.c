/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:08:48 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 23:05:37 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dda(t_fdf *fdf, float x1, float x2, float y1, float y2, int color)
{
	float	dy;
	float	dx;
	float	c;
	int		i;
	char	*dst;

	dx = (x2 - x1);
	dy = (y2 - y1);
	if (fabs(dx) > fabs(dy))
		c = fabs(dx);
	else
		c = fabs(dy);
	i = 0;
	dx /= c;
	dy /= c;
	while (i <= c)
	{
		if (y1 >= 0 && x1 >= 0 && y1 < SCREEN_H && x1 < SCREEN_W)
		{
			dst = fdf->addr + (int)((int)y1 * fdf->line_size + (int)x1 * fdf->bpp);
			*(unsigned int*)dst = color;
		}
		y1 += dy;
		x1 += dx;
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
