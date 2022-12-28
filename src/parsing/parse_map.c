/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:38:47 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 12:45:10 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

short	read_height(char *buffer, int fd, int *idx)
{
	char	sign;
	short	num;

	sign = 1;
	num = 0;
	if (buffer[*idx] == '-')
	{
		sign = -1;
		*idx += 1;
	}
	while (*idx != -1)
	{
		while (buffer[*idx] != '\0')
		{
			if (!ft_isdigit(buffer[*idx]))
				return (sign * num);
			num = num * 10 + buffer[*idx] - '0';
			*idx += 1;
		}
		*idx = 0;
		buffer[read(fd, buffer, BUFFER_SIZE)] = '\0';
		if (buffer[0] == '\0')
			*idx = -1;
	}
	return (sign * num);
}

void	skip_to_color(char *buffer, int *i, int fd)
{
	while (buffer[*i] != 'x' && buffer[*i] != 'X')
	{
		*i += 1;
		if (buffer[*i] == '\0')
		{
			*i = 0;
			buffer[read(fd, buffer, BUFFER_SIZE)] = '\0';
		}
	}
	*i += 1;
	if (buffer[*i] == '\0')
	{
		*i = 0;
		buffer[read(fd, buffer, BUFFER_SIZE)] = '\0';
	}
}

int	read_color(char *buffer, int fd, int *idx)
{
	int	color;

	skip_to_color(buffer, idx, fd);
	color = 0;
	while (*idx != -1)
	{
		while (buffer[*idx] != '\0')
		{
			if (buffer[*idx] >= 'a' && buffer[*idx] <= 'f')
				color = color * 16 + buffer[*idx] - 'a' + 10;
			else if (buffer[*idx] >= 'A' && buffer[*idx] <= 'F')
				color = color * 16 + buffer[*idx] - 'A' + 10;
			else if (ft_isdigit(buffer[*idx]))
				color = color * 16 + buffer[*idx] - '0';
			else
				return (color);
			*idx += 1;
		}
		*idx = 0;
		buffer[read(fd, buffer, BUFFER_SIZE)] = '\0';
		if (buffer[0] == '\0')
			*idx = -1;
	}
	return (color);
}

void	next_point(char *buffer, int *idx, t_fdf *fdf)
{
	while (*idx < BUFFER_SIZE)
	{
		if (buffer[*idx] == '\n')
		{
			fdf->height++;
			if (fdf->width == 0)
				fdf->width = fdf->point_count;
		}
		if (is_space(buffer[*idx]))
			break ;
		*idx += 1;
	}
}

void	parse_map(t_fdf *fdf, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		i;

	buffer[0] = '\0';
	i = 0;
	while (1)
	{
		skip_whitespace(buffer, fd, &i);
		if (i == -1)
			return ;
		fdf->points[fdf->point_count].height = read_height(buffer, fd, &i);
		if (i == -1)
			return ;
		fdf->points[fdf->point_count].color = fdf->theme;
		if (buffer[i] == ',')
			fdf->points[fdf->point_count].color = read_color(buffer, fd, &i);
		fdf->point_count++;
		if (fdf->point_count >= fdf->max_size)
			resize_points(fdf);
		if (fdf->points == NULL)
			return ;
		next_point(buffer, &i, fdf);
	}
}
