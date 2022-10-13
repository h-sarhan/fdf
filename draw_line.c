/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:47:37 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 18:30:47 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_points_low(t_point **pts, t_vars *vars, int *dxy, int *dyi)
{
	int	xy[2];
	int	color;

	xy[0] = pts[0]->x;
	xy[1] = pts[0]->y;
	while (xy[0] < pts[1]->x)
	{
		if (pts[1]->color == pts[0]->color && pts[0]->color == -1)
			color = vars->theme;
		else if (pts[1]->color == pts[0]->color)
			color = pts[0]->color;
		else
			color = color_mix(pts[0]->color, pts[1]->color,
					(float)(xy[0] - pts[0]->x) / (pts[1]->x - pts[0]->x));
		my_mlx_pixel_put(xy[0], xy[1], color, vars);
		if (dyi[0] > 0)
		{
			xy[1] = xy[1] + dyi[1];
			dyi[0] = dyi[0] + (2 * (dxy[1] - dxy[0]));
		}
		else
			dyi[0] = dyi[0] + 2 * dxy[1];
		xy[0]++;
	}
}

void	draw_line_low( t_point *p1, t_point *p2, t_vars *vars)
{
	int		dxy[2];
	int		dyi[2];
	t_point	*pts[2];

	dxy[0] = p2->x - p1->x;
	dxy[1] = p2->y - p1->y;
	dyi[1] = 1;
	if (dxy[1] < 0)
	{
		dyi[1] = -1;
		dxy[1] = -dxy[1];
	}
	dyi[0] = (2 * dxy[1]) - dxy[0];
	pts[0] = p1;
	pts[1] = p2;
	draw_line_points_low(pts, vars, dxy, dyi);
}

void	draw_line_points_high(t_point **pts, t_vars *vars, int *dxy, int *dxi)
{
	int	xy[2];
	int	color;

	xy[0] = pts[0]->x;
	xy[1] = pts[0]->y;
	while (xy[1] < pts[1]->y)
	{
		if (pts[1]->color == pts[0]->color && pts[0]->color == -1)
			color = vars->theme;
		else if (pts[1]->color == pts[0]->color)
			color = pts[0]->color;
		else
			color = color_mix(pts[0]->color, pts[1]->color,
					(float)(xy[1] - pts[0]->y) / (pts[1]->y - pts[0]->y));
		my_mlx_pixel_put(xy[0], xy[1], color, vars);
		if (dxi[0] > 0)
		{
			xy[0] = xy[0] + dxi[1];
			dxi[0] = dxi[0] + (2 * (dxy[0] - dxy[1]));
		}
		else
			dxi[0] = dxi[0] + 2 * dxy[0];
		xy[1]++;
	}
}

void	draw_line_high(t_point *p1, t_point *p2, t_vars *vars)
{
	int		dxy[2];
	int		dxi[2];
	t_point	*pts[2];

	dxy[0] = p2->x - p1->x;
	dxy[1] = p2->y - p1->y;
	dxi[1] = 1;
	if (dxy[0] < 0)
	{
		dxi[1] = -1;
		dxy[0] = -dxy[0];
	}
	dxi[0] = (2 * dxy[0]) - dxy[1];
	pts[0] = p1;
	pts[1] = p2;
	draw_line_points_high(pts, vars, dxy, dxi);
}

// Bresenham's line drawing algorithm
void	draw_line(t_point *p1, t_point *p2, t_vars *vars)
{
	if (fabs(p2->y - p1->y) < fabs(p2->x - p1->x))
	{
		if (p1->x > p2->x)
			draw_line_low(p2, p1, vars);
		else
			draw_line_low(p1, p2, vars);
	}
	else
	{
		if (p1->y > p2->y)
			draw_line_high(p2, p1, vars);
		else
			draw_line_high(p1, p2, vars);
	}
}
