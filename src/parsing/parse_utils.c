/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:57:47 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 16:57:28 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	resize_points(t_fdf *fdf, size_t new_size)
{
	t_point	*new_points;

	new_points = malloc(new_size * sizeof(t_point));
	if (new_points == NULL)
	{
		free(fdf->points);
		fdf->points = NULL;
		return ;
	}
	ft_memcpy(new_points, fdf->points, sizeof(t_point) * fdf->point_count);
	free(fdf->points);
	fdf->points = new_points;
	fdf->max_size = new_size;
}

void	skip_whitespace(t_fdf *fdf, char *buffer, int fd, int *idx)
{
	while (*idx != -1)
	{
		while (buffer[*idx] != '\0')
		{
			if (is_space(buffer[*idx]) == false)
				return ;
			*idx += 1;
		}
		*idx = 0;
		buffer[read(fd, buffer, BUFFER_SIZE)] = '\0';
		if (buffer[0] == '\0')
			*idx = -1;
	}
}

uint8_t	add_color(t_fdf *fdf, char *buffer, int fd, int *idx)
{
	int				color;
	uint8_t			i;

	color = read_color(buffer, fd, idx);
	i = 0;
	while (i < fdf->num_colors)
	{
		if (fdf->colors[i] == color)
			return (i);
		i++;
	}
	fdf->colors[fdf->num_colors] = color;
	fdf->num_colors++;
	return (i);
}
