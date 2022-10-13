/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:53:22 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 17:56:42 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Create a map struct
t_map	*create_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		exit_msg("ERROR CREATING MAP\n", EXIT_FAILURE);
	map->min_x = INT_MAX;
	map->max_x = INT_MIN;
	map->min_y = INT_MAX;
	map->max_y = INT_MIN;
	map->max_og_x = INT_MIN;
	map->max_og_y = INT_MIN;
	map->max_og_z = INT_MIN;
	map->orientation = create_quaternion(0, 0, 0, 1);
	if (map->orientation == NULL)
	{
		free(map);
		exit_msg("ERROR CREATING MAP\n", EXIT_FAILURE);
	}
	rotate_z(map, 45);
	rotate_x(map, asin(tan(30 * (PI / 180.0f))) / (PI / 180.0f) + 30);
	return (map);
}

// Create a point
t_point	*create_point(float x, float y, float z, int color)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	if (point == NULL)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = color;
	return (point);
}

// Free a map
void	free_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			free(map->proj_pts[i][j]);
			free(map->points[i][j]);
			free(map->points_copy[i][j]);
			j++;
		}
		free(map->proj_pts[i]);
		free(map->points[i]);
		free(map->points_copy[i]);
		i++;
	}
	free(map->proj_pts);
	free(map->points);
	free(map->points_copy);
	free(map->orientation);
	free(map);
}
