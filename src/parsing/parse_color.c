/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:57:54 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 05:29:39 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_rest_of_color(t_fdf *fdf, int color, int fd)
{
	int		flag;
	char	ch;

	if (color == -2)
	{
		flag = read(fd, &ch, 1);
		if (flag < 1)
			return 0;
		flag = read(fd, &ch, 1);
		if (flag < 1)
			return 0;
		
	}
	while (1)
	{
		flag = read(fd, &ch, 1);
		if (flag == 0 || check_space(fdf, ch))
		{
			if (flag == 0 && ch != '\n')
				fdf->height++;
			break;
		}
		if (((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f')
			|| (ch >= 'A' && ch <= 'F')) && ch != '\0')
		{
			color *= 16;
			if (ch >= '0' && ch <= '9')
				color += ch - '0';
			else if (ch >= 'a' && ch <= 'f')
				color += ch - 'a' + 10;
			else
				color += ch - 'A' + 10;
		}
		else
			break;
	}
	return color;
}

int	get_color(t_fdf *fdf, const char *buff, int *idx, int fd)
{
	unsigned int	color;
	int				i;
	char			ch;

	color = 0;
	i = 0;
	while (check_space(fdf, buff[i]) == true && buff[i] != '\0')
		i++;
	if (buff[i] == '0' && (buff[i + 1] == 'x' || buff[i + 1] == 'X'))
		i += 2;
	while (((buff[i] >= '0' && buff[i] <= '9') || (buff[i] >= 'a' && buff[i] <= 'f')
		|| (buff[i] >= 'A' && buff[i] <= 'F')) && buff[i] != '\0')
	{
		color *= 16;
		if (buff[i] >= '0' && buff[i] <= '9')
			color += buff[i] - '0';
		else if (buff[i] >= 'a' && buff[i] <= 'f')
			color += buff[i] - 'a' + 10;
		else
			color += buff[i] - 'A' + 10;
		i++;
	}
	return (color);
}
