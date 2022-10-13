/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ppm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 00:00:04 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 18:31:46 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_ppm_header(int fd, int *w, int *h)
{
	char			*header;
	char			**tokens;

	header = get_next_line(fd);
	if (header == NULL || ft_strncmp(header, "P6\n", ft_strlen(header)) != 0)
		exit_msg("ERROR READING FILE\n", EXIT_FAILURE);
	free(header);
	header = get_next_line(fd);
	if (header == NULL)
		exit_msg("ERROR READING FILE\n", EXIT_FAILURE);
	tokens = ft_split(header, ' ');
	free(header);
	if (tokens == NULL)
		exit_msg("ERROR READING FILE\n", EXIT_FAILURE);
	*w = ft_atoi(tokens[0]);
	*h = ft_atoi(tokens[1]);
	free_split_array(tokens);
	header = get_next_line(fd);
	if (header == NULL)
		exit_msg("ERROR READING FILE\n", EXIT_FAILURE);
	free(header);
}

int	read_ppm_color(int fd)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	if (read(fd, &g, 1) < 0)
		exit_msg("ERROR READING FILE\n", EXIT_FAILURE);
	if (read(fd, &b, 1) < 0)
		exit_msg("ERROR READING FILE\n", EXIT_FAILURE);
	if (read(fd, &r, 1) < 0)
		exit_msg("ERROR READING FILE\n", EXIT_FAILURE);
	return (create_trgb(0, r, g, b));
}

void	fill_map(int fd, t_map *map, int scale)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->num_rows)
	{
		map->points[i] = ft_calloc(map->num_cols + 1, sizeof(t_point *));
		map->points_copy[i] = ft_calloc(map->num_cols + 1, sizeof(t_point *));
		map->proj_pts[i] = ft_calloc(map->num_cols + 1, sizeof(t_point *));
		if (map->points[i] == NULL || map->points_copy[i] == NULL
			|| map->proj_pts == NULL)
			exit_msg("Error reading file", EXIT_FAILURE);
		j = 0;
		while (j < map->num_cols)
		{
			map->proj_pts[i][j] = create_point(0, 0, 0, read_ppm_color(fd));
			map->points[i][j] = create_point(i * scale,
					(map->num_rows - j) * scale, 0, 0);
			map->points_copy[i][j] = create_point(i * scale,
					(map->num_rows - j) * scale, 0, 0);
			j++;
		}
		i++;
	}
}

t_map	*read_map_from_ppm(char *img_path)
{
	int		fd;
	t_map	*map;
	int		scale;

	fd = open(img_path, O_RDONLY);
	if (fd == -1)
		exit_msg("COULD NOT OPEN FILE\n", EXIT_FAILURE);
	map = create_map();
	if (map == NULL)
		exit_msg("ERROR READING FILE\n", EXIT_FAILURE);
	read_ppm_header(fd, &map->num_cols, &map->num_rows);
	scale = 1;
	while (map->num_cols * scale < 400 && map->num_rows * scale < 400)
		scale++;
	map->points = ft_calloc(map->num_rows + 1, sizeof(t_point **));
	map->points_copy = ft_calloc(map->num_rows + 1, sizeof(t_point **));
	map->proj_pts = ft_calloc(map->num_rows + 1, sizeof(t_point **));
	if (map->points == NULL || map->points_copy == NULL
		|| map->proj_pts == NULL)
		exit_msg("ERROR READING FILE\n", EXIT_FAILURE);
	fill_map(fd, map, scale);
	find_min_max(map, map->points);
	rotate_points(map);
	project_points(map, scale, 'i');
	return (map);
}
