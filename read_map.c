/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:19:09 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 18:30:55 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list	*fill_lines(int *rows_cols, char *line, int fd)
{
	t_list	*lines;

	lines = NULL;
	rows_cols[0] = 0;
	while (line != NULL)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		rows_cols[0]++;
		line = get_next_line(fd);
	}
	return (lines);
}

t_map	*read_map_start(char *map_path, int *rows_cols, char **line,
		t_list **lines)
{
	int		i;
	t_map	*map;
	char	**tokens;
	int		fd;

	i = 0;
	map = create_map();
	fd = open(map_path, O_RDONLY);
	*line = get_next_line(fd);
	tokens = ft_split(*line, ' ');
	if (*line == NULL || tokens == NULL)
	{
		if (*line != NULL)
			free(*line);
		free_map(map);
		exit_msg("ERROR READING MAP\n", EXIT_FAILURE);
	}
	while (tokens[i] != NULL)
		i++;
	free_split_array(tokens);
	rows_cols[1] = i;
	*lines = fill_lines(rows_cols, *line, fd);
	close(fd);
	return (map);
}

void	init_points(t_map *map, int *rowcol)
{
	int	ij[2];

	map->points = ft_calloc(rowcol[0] + 1, sizeof(t_point **));
	map->points_copy = ft_calloc(rowcol[0] + 1, sizeof(t_point **));
	map->proj_pts = ft_calloc(rowcol[0] + 1, sizeof(t_point **));
	if (!map->points || !map->points_copy || !map->proj_pts)
		exit_msg("ERROR READING MAP", EXIT_FAILURE);
	ij[0] = -1;
	while (++ij[0] < rowcol[0])
	{
		map->points[ij[0]] = ft_calloc(rowcol[1] + 1, sizeof(t_point *));
		map->points_copy[ij[0]] = ft_calloc(rowcol[1] + 1, sizeof(t_point *));
		map->proj_pts[ij[0]] = ft_calloc(rowcol[1] + 1, sizeof(t_point *));
		if (!map->points || !map->points_copy || !map->proj_pts)
			exit_msg("ERROR READING MAP", EXIT_FAILURE);
		ij[1] = -1;
		while (++ij[1] < rowcol[1])
		{
			map->points[ij[0]][ij[1]] = ft_calloc(1, sizeof(t_point));
			map->points_copy[ij[0]][ij[1]] = ft_calloc(1, sizeof(t_point));
			map->proj_pts[ij[0]][ij[1]] = ft_calloc(1, sizeof(t_point));
			if (!map->points || !map->points_copy || !map->proj_pts)
				exit_msg("ERROR READING MAP", EXIT_FAILURE);
		}
	}
}

void	fill_map2(t_map *map, int *rows_cols, t_list *lines, float scale)
{
	int		i;
	int		j;
	char	**tks;
	char	*line;

	i = -1;
	init_points(map, rows_cols);
	while (++i < rows_cols[0] && lines != NULL)
	{
		line = lines->content;
		tks = ft_split(line, ' ');
		j = -1;
		while (++j < rows_cols[1] && tks[j] != NULL)
		{
			if (ft_strchr(tks[j], ',') != NULL)
				map->proj_pts[i][j]->color = hextoi(ft_strchr(tks[j], ',') + 1);
			else
				map->proj_pts[i][j]->color = -1;
			map->points[i][j]->x = i * scale;
			map->points[i][j]->y = (rows_cols[1] - j) * scale;
			map->points[i][j]->z = ft_atoi(tks[j]) * scale;
		}
		lines = lines->next;
		free_split_array(tks);
	}
}

t_map	*read_map(char *map_path)
{
	char	*line;
	t_list	*lines;
	t_map	*map;
	float	scale;
	int		rows_cols[2];

	map = read_map_start(map_path, rows_cols, &line, &lines);
	scale = 1;
	while (scale * rows_cols[1] < 400 || scale * rows_cols[0] < 300)
		scale += 1;
	map->num_rows = rows_cols[0];
	map->num_cols = rows_cols[1];
	fill_map2(map, rows_cols, lines, scale);
	find_min_max(map, map->points);
	rotate_points(map);
	project_points(map, 1, 'i');
	ft_lstclear(&lines, free);
	return (map);
}
