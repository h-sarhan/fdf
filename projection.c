/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:21:09 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 17:56:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project_point(t_point *projected, t_point *orig, char proj)
{
	if (proj == 'i')
	{
		projected->x = orig->x;
		projected->y = orig->y;
	}
	else if (proj == 'c')
	{
		projected->x = orig->x + 0.5 * orig->z * cos(63.4 * (PI / 180.0f));
		projected->y = orig->y + -0.5 * orig->z * sin(63.4 * (PI / 180.0f));
		projected->z = 0;
	}
}

void	check_min_max(t_map *map, t_point *point)
{
	if (point->x < map->min_x)
		map->min_x = point->x;
	if (point->y < map->min_y)
		map->min_y = point->y;
	if (point->x > map->max_x)
		map->max_x = point->x;
	if (point->y > map->max_y)
		map->max_y = point->y;
}

void	scale_point(t_point *p, float scale)
{
	p->x *= scale;
	p->y *= scale;
	p->z *= scale;
}

void	translate_to_origin(t_point *p, t_map *map, char sign)
{
	if (sign == '+')
	{
		p->x += map->max_og_x / 2.0f;
		p->y += map->max_og_y / 2.0f;
		p->z += map->max_og_z / 2.0f;
	}
	else if (sign == '-')
	{
		p->x -= map->max_og_x / 2.0f;
		p->y -= map->max_og_y / 2.0f;
		p->z -= map->max_og_z / 2.0f;
	}
}

void	project_points(t_map *map, float scale, char proj)
{
	int		i;
	int		j;
	t_point	***projected_points;
	t_point	***points;

	points = map->points_copy;
	projected_points = map->proj_pts;
	i = 0;
	map->min_x = INT_MAX;
	map->min_y = INT_MAX;
	map->max_x = INT_MIN;
	map->max_y = INT_MIN;
	while (i < map->num_rows)
	{
		j = -1;
		while (++j < map->num_cols)
		{
			project_point(projected_points[i][j], points[i][j], proj);
			translate_to_origin(projected_points[i][j], map, '-');
			scale_point(projected_points[i][j], scale);
			translate_to_origin(projected_points[i][j], map, '+');
			check_min_max(map, projected_points[i][j]);
		}
		i++;
	}
}
