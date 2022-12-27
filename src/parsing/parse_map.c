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

int	get_num(const char *buff, int *start)
{
	int	num;
	int	i;
	int	sign;

	num = 0;
	i = *start;
	sign = 1;
	while (is_space(buff[i]))
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
		*start = i;
	return (num * sign);
}

void	read_values(const char *buffer, int bytes_read)
{
	int	buff_idx;
	int	num;

	buff_idx = 0;
	printf("%s\n", buffer);
	while (buff_idx < bytes_read)
	{
		num = get_num(buffer, &buff_idx);
		if (buffer[buff_idx] == '\0' && bytes_read == BUFFER_SIZE)
			break ;
		// printf("%d ", num);
		while (is_space(buffer[buff_idx]))
		{
			if (buffer[buff_idx] == '\n')
				printf("\n");
			buff_idx++;
		}
	}
}

void	parse_map(t_fdf *fdf, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	int		point_count;
	(void)point_count;

	fdf->points = malloc(500 * sizeof(t_fdf));
	if (fdf->points == NULL)
	{
		printf("FAILED TO MALLOC\n");
		return ;
	}
	fdf->colors = malloc(500 * sizeof(int));
	if (fdf->colors == NULL)
	{
		printf("FAILED TO MALLOC\n");
		return ;
	}
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(fdf->points);
			printf("FAILED TO READ\n");
			return ;
		}
		buffer[bytes_read] = '\0';
		if (bytes_read != (BUFFER_SIZE))
		{
			printf("BROKE\n");
			break ;
		}
		read_values(buffer, bytes_read);
	}
	if (ft_strlen(buffer) > 0)
	{
		// MORE NUMBERS LEFT IN THE BUFFER
		read_values(buffer, bytes_read);
	}
}