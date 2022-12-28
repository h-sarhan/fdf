/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:58:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 14:41:19 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_points(t_fdf *fdf)
{
	printf("\nHeight: %u\n", fdf->height);
	printf("Width: %u\n", fdf->width);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	int		fd;

	ft_bzero(&fdf, sizeof(t_fdf));
	fdf.max_size = MAX_POINT_COUNT;
	fdf.colors[0] = 0xffffff;
	if (argc != 2)
	{
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("FAILED TO OPEN\n");
		exit(1);
	}
	fdf.points = malloc(MAX_POINT_COUNT * sizeof(t_point));
	if (fdf.points == NULL)
		exit(!printf("FAILED TO MALLOC\n"));
	parse_map(&fdf, fd);
	if (fdf.points == NULL)
		exit(!printf("FAILED TO MALLOC\n"));
	close(fd);
	resize_points(&fdf, fdf.point_count);
	print_points(&fdf);
	free(fdf.points);
}
