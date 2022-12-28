/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:38:47 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 01:56:01 by hsarhan          ###   ########.fr       */
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



int	check_space(t_fdf *fdf, char c)
{
	if (c == '\n')
	{
		if (fdf->width == 0)
			fdf->width = fdf->point_count;
		fdf->height++;
		return (true);
	}
	return (c == ' ' || c == '\f'
		|| c == '\r'
		|| c == '\t' || c == '\v');
}

int	get_num_digits(int num)
{
	int	num_digits;

	num_digits = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		num_digits++;
	}
	return (num_digits);
}

int	parse_rest(t_fdf *fdf, int num, int fd)
{
	int		flag;
	char	ch;

	while (1)
	{
		flag = read(fd, &ch, 1);
		if (flag == 0 || check_space(fdf, ch))
		{
			if (flag == 0 && ch != '\n')
				fdf->height++;
			break;
		}
		if (ch >= '0' && ch <= '9')
		{
			num *= 10;
			num += ch - '0';
		}
		else
			break;
	}
	return num;
}

int	get_num(t_fdf *fdf, const char *buff, int *idx, int fd)
{
	int	num;
	int	i;
	int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while (check_space(fdf, buff[i]))
		i++;
	if (buff[i] == '+' || buff[i] == '-')
	{
		if (buff[i] == '-')
			sign = -1;
		i++;
	}
	while (buff[i] >= '0' && buff[i] <= '9')
	{
		num *= 10;
		num += buff[i++] - '0';
	}
	if (buff[i] != '\0')
		*idx += i;
	if (buff[i] == '\0')
		return (sign * parse_rest(fdf, num, fd));
	return (num * sign);
}

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
			fdf->points[fdf->point_count].height = get_num(fdf, &buffer[buff_idx], &new_idx, fd);
			fdf->points[fdf->point_count].color = 0xffffff;
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
		while (check_space(fdf, buffer[buff_idx]) && buffer[buff_idx] != '\0')
		{
			buff_idx++;
		}
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