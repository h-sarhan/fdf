/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 17:51:14 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Find the minimum and maximum x,y,z values of the points before transformation
void	find_min_max(t_map *map, t_point ***points)
{
	int	i;
	int	j;
	int	max_xyz[3];

	max_xyz[0] = INT_MIN;
	max_xyz[1] = INT_MIN;
	max_xyz[2] = INT_MIN;
	i = 0;
	while (i < map->num_rows)
	{
		j = -1;
		while (++j < map->num_cols)
		{
			if (points[i][j]->x > max_xyz[0])
				max_xyz[0] = points[i][j]->x;
			if (points[i][j]->y > max_xyz[1])
				max_xyz[1] = points[i][j]->y;
			if (points[i][j]->z > max_xyz[2])
				max_xyz[2] = points[i][j]->z;
		}
		i++;
	}
	map->max_og_x = max_xyz[0];
	map->max_og_y = max_xyz[1];
	map->max_og_z = max_xyz[2];
}

// Put pixel on an image
void	my_mlx_pixel_put(int x, int y, int color, t_vars *vars)
{
	char	*dst;
	t_data	*data;

	x += vars->translate_x;
	y += vars->translate_y;
	if (x < 0 || y < 0 || x >= vars->win_x || y >= vars->win_y)
		return ;
	data = vars->data;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// Display control messages
void	display_controls(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->win, 50, 50, vars->theme, "[CONTROLS]:");
	mlx_string_put(vars->mlx, vars->win, 70, 70, vars->theme, "WASD:"
		"         Pan");
	mlx_string_put(vars->mlx, vars->win, 70, 90, vars->theme, "LEFT/RIGHT:"
		"   Rotate X");
	mlx_string_put(vars->mlx, vars->win, 70, 110, vars->theme, "UP/DOWN:"
		"      Rotate Y");
	mlx_string_put(vars->mlx, vars->win, 70, 130, vars->theme, "Q/E:"
		"          Rotate Z");
	mlx_string_put(vars->mlx, vars->win, 70, 150, vars->theme, "+/-:"
		"          Zoom In/Out");
	mlx_string_put(vars->mlx, vars->win, 70, 170, vars->theme, "MIDDLE MOUSE:"
		" Rotate Freely");
	mlx_string_put(vars->mlx, vars->win, 70, 190, vars->theme, "MOUSE SCROLL:"
		" Zoom In/Out");
	mlx_string_put(vars->mlx, vars->win, 70, 210, vars->theme, "C:"
		"            Switch Theme");
}

// Draw a frame
void	draw_frame(t_vars *vars)
{
	int		i;
	int		j;
	t_point	***points;
	void	*old_img;

	i = 0;
	j = 0;
	points = vars->map->proj_pts;
	old_img = create_new_image(vars);
	while (i < vars->map->num_rows)
	{
		j = -1;
		while (++j < vars->map->num_cols)
		{
			if (j + 1 < vars->map->num_cols)
				draw_line(points[i][j], points[i][j + 1], vars);
			if (i + 1 < vars->map->num_rows)
				draw_line(points[i][j], points[i + 1][j], vars);
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_destroy_image(vars->mlx, old_img);
	display_controls(vars);
}
