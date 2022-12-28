/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:38:47 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 12:05:16 by hsarhan          ###   ########.fr       */
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

void	skip_whitespace(char *buffer, int fd, int *idx)
{
	while (*idx != -1)
	{
		while (buffer[*idx] != '\0')
		{
			// if (is_space(buffer[*idx]) == false && buffer[*idx] != '\n')
			if (is_space(buffer[*idx]) == false)
				return ;
			*idx += 1;
		}
		*idx = 0;
		buffer[read(fd, buffer, BUFFER_SIZE)]  = '\0';
		if (buffer[0] == '\0')
			*idx = -1;
	}
}

int	read_height(char *buffer, int fd, int *idx)
{
	int	sign;
	int	num;

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
		buffer[read(fd, buffer, BUFFER_SIZE)]  = '\0';
		if (buffer[0] == '\0')
			*idx = -1;
	}
	return (sign * num);
}

int	read_color(char *buffer, int fd, int *idx)
{
	int	color;

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
		buffer[read(fd, buffer, BUFFER_SIZE)]  = '\0';
		if (buffer[0] == '\0')
			*idx = -1;
	}
	return (color);
}

void	parse_map(t_fdf *fdf, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		i;
	int		color;
	

	fdf->points = malloc(MAX_POINT_COUNT * sizeof(t_point));
	if (fdf->points == NULL)
		exit(!printf("FAILED TO MALLOC\n"));
	buffer[0] = '\0';
	i = 0;
	while (1)
	{
		skip_whitespace(buffer, fd, &i);
		if (i == -1)
		{
			printf("End of file has been reached\n");
			return ;
		}
		int height = read_height(buffer, fd, &i);
		if (i == -1)
		{
			printf("End of file has been reached\n");
			return ;
		}
		// if (buffer[i] != ',')
		// 	printf("%d ", height);
		if (buffer[i] == ',')
		{
			// printf("stck here\n");
			while (buffer[i] != 'x' && buffer[i] != 'X')
			{
				i++;
				if (buffer[i] == '\0')
				{
					i = 0;
					buffer[read(fd, buffer, BUFFER_SIZE)]  = '\0';
				}
			}
			i++;
			if (buffer[i] == '\0')
			{
				i = 0;
				buffer[read(fd, buffer, BUFFER_SIZE)]  = '\0';
			}
			color = read_color(buffer, fd, &i);
			// printf("%d,0X%X ", height, color);
		}
		while (i < BUFFER_SIZE)
		{
			if (buffer[i] == '\n')
				printf("\n");
			if (is_space(buffer[i]))
				break;
			i++;
		}
	}
}