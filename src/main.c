/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:58:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 15:29:32 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_points(t_fdf *fdf)
{
	printf("\nHeight: %u\n", fdf->max_y);
	printf("Width: %u\n", fdf->max_x);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	int		fd;

	ft_bzero(&fdf, sizeof(t_fdf));
	fdf.max_size = MAX_POINT_COUNT;
	fdf.max_z = INT16_MIN;
	fdf.min_z = INT16_MAX;
	fdf.colors[0] = 0xffffff;
	identity_matrix(&fdf.transform_mat);
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
	// draw_points(&fdf);
	print_points(&fdf);
	free(fdf.points);
}
