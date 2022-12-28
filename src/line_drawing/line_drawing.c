/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:08:48 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 20:47:16 by hsarhan          ###   ########.fr       */
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
		if (y1 < 0 || x1 < 0 || y1 >= SCREEN_H || x1 >= SCREEN_W)
			break ;
		dst = fdf->addr + (int)((int)y1 * fdf->line_size + (int)x1 * fdf->bpp);
		*(unsigned int*)dst = color;
		y1 += dy;
		x1 += dx;
		i++;
	}
}