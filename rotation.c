/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:20:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 15:28:56 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_map *map, float rot)
{
	t_point			axis;
	t_quaternion	*q_rot;

	axis.x = 1;
	axis.y = 0;
	axis.z = 0;
	q_rot = create_quaternion_rotation(rot * (PI / 180.0f), &axis);
	map->orientation = rotate_quaternion(q_rot, map->orientation);
}

void	rotate_y(t_map *map, float rot)
{
	t_point			axis;
	t_quaternion	*q_rot;

	axis.x = 0;
	axis.y = -1;
	axis.z = 0;
	q_rot = create_quaternion_rotation(rot * (PI / 180.0f), &axis);
	map->orientation = rotate_quaternion(q_rot, map->orientation);
}

void	rotate_z(t_map *map, float rot)
{
	t_point			axis;
	t_quaternion	*q_rot;

	axis.x = 0;
	axis.y = 0;
	axis.z = 1;
	q_rot = create_quaternion_rotation(rot * (PI / 180.0f), &axis);
	map->orientation = rotate_quaternion(q_rot, map->orientation);
}

void	rotate_points(t_map *map)
{
	int		i;
	int		j;
	t_point	***points;
	t_point	***points_copy;

	points = map->points;
	points_copy = map->points_copy;
	i = 0;
	while (i < map->num_rows)
	{
		j = -1;
		while (++j < map->num_cols)
		{
			points_copy[i][j]->x = points[i][j]->x - (map->max_og_x / 2.0f);
			points_copy[i][j]->y = points[i][j]->y - (map->max_og_y / 2.0f);
			points_copy[i][j]->z = points[i][j]->z - (map->max_og_z / 2.0f);
			rotate_point(map->orientation, points_copy[i][j]);
			points_copy[i][j]->x += (map->max_og_x / 2.0f);
			points_copy[i][j]->y += (map->max_og_y / 2.0f);
			points_copy[i][j]->z += (map->max_og_z / 2.0f);
		}
		i++;
	}
}
