/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:57:47 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 12:44:56 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	resize_points(t_fdf *fdf)
{
	t_point	*new_points;

	new_points = malloc(fdf->point_count * 4 * sizeof(t_point));
	if (new_points == NULL)
	{
		free(fdf->points);
		fdf->points = NULL;
		return ;
	}
	ft_memcpy(new_points, fdf->points, sizeof(t_point) * fdf->point_count);
	free(fdf->points);
	fdf->points = new_points;
	fdf->max_size *= 4;
}

void	skip_whitespace(char *buffer, int fd, int *idx)
{
	while (*idx != -1)
	{
		while (buffer[*idx] != '\0')
		{
			if (is_space(buffer[*idx]) == false && buffer[*idx] != '\n')
				return ;
			*idx += 1;
		}
		*idx = 0;
		buffer[read(fd, buffer, BUFFER_SIZE)] = '\0';
		if (buffer[0] == '\0')
			*idx = -1;
	}
}
