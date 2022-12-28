/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:38:47 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 05:31:20 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// 2344234241 1 1 1 1
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202
// 1,0x810202 1,0x810202 1,0x810202 1,0x810202 1,0x810202


void	resize_points(t_fdf *fdf)
{
	t_point	*new_points;

	new_points = malloc(fdf->point_count * 2 * sizeof(t_point));
	ft_memcpy(new_points, fdf->points, sizeof(t_point) * fdf->point_count);
	free(fdf->points);
	fdf->points = new_points;
}

char	*ft_strjoin_free(char *s1, char *s2, int fre)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = ft_strjoin(s1, s2);
	if (fre == 1 || fre == 3)
		free(s1);
	if (fre == 2 || fre == 3)
		free(s2);
	return (str);
}
void	read_values(t_fdf *fdf, char *buffer, int bytes_read, int fd)
{
	int	buff_idx;
	int	new_idx;

	buff_idx = 0;
	while (buff_idx < bytes_read)
	{
		if (!check_space(fdf, buffer[buff_idx]))
		{
			new_idx = buff_idx;
			fdf->points[fdf->point_count].height = get_height(fdf, &buffer[buff_idx], &new_idx, fd);
			// if (buff_idx == new_idx)
			// 	fdf->points[fdf->point_count].color = get_color(fdf, NULL, &new_idx, fd);
			// else
			// 	fdf->points[fdf->point_count].color = get_color(fdf, &buffer[new_idx], &new_idx, fd);
			fdf->point_count++;
			if (fdf->point_count == fdf->max_size)
			{
				resize_points(fdf);
				fdf->max_size *= 2;
			}
			if (buff_idx == new_idx)
				return ;
			buff_idx = new_idx;
		}
		buff_idx++;
		// while (check_space(fdf, buffer[buff_idx]) && buffer[buff_idx] != '\0')
		// {
		// 	buff_idx++;
		// }
		if (buffer[buff_idx] == '\0')
			return ;
	}
	return ;
}

void	parse_map(t_fdf *fdf, int fd)
{
	char	*buffer;
	int		bytes_read;

	fdf->points = malloc(MAX_POINT_COUNT * sizeof(t_point));
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fdf->points == NULL)
	{
		printf("FAILED TO MALLOC\n");
		return ;
	}
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			printf("FAILED TO READ\n");
			return ;
		}
		buffer[bytes_read] = '\0';
		if (bytes_read != (BUFFER_SIZE))
		{
			// printf("BROKE\n");
			if (buffer[bytes_read - 1] != '\n')
				fdf->height++;
			break ;
		}
		read_values(fdf, buffer, bytes_read, fd);
	}
	if (ft_strlen(buffer) > 0)
	{
		// MORE NUMBERS LEFT IN THE BUFFER
		read_values(fdf, buffer, bytes_read, fd);
	}
	free(buffer);
}