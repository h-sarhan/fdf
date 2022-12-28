/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_height.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 04:57:47 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 05:38:35 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_space(t_fdf *fdf, char c)
{
	if (c == '\n')
	{
		if (fdf->width == 0)
			fdf->width = fdf->point_count;
		return (true);
	}
	return (c == ' ' || c == '\f'
		|| c == '\r'
		|| c == '\t' || c == '\v');
}

int	parse_rest_of_height(t_fdf *fdf, int num, int fd)
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

int	get_height(t_fdf *fdf, const char *buff, int *idx, int fd)
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
	check_space(fdf, buff[i]);
	if (buff[i] != '\0')
		*idx += i;
	if (buff[i] == '\0')
		return (sign * parse_rest_of_height(fdf, num, fd));
	return (num * sign);
}