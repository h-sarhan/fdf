/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:58:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 16:11:04 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_points(t_fdf *fdf)
{
	t_vector	vec;
	t_vector	transformed;

	for (int i = 0; i < fdf->point_count; i++)
	{
		vec.x = i % fdf->max_x;
		vec.y = i / fdf->max_x;
		vec.z = fdf->points[i].height;
		vec.w = 1;
		mat_vec_multiply(&transformed, &fdf->transform_mat, &vec);
		printf("x = %.1f, ", transformed.x);
		printf("y = %.1f, ", transformed.y);
		printf("z = %.1f\n", transformed.z);
	}
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
	fdf.scale = 20;
	resize_points(&fdf, fdf.point_count);
	calculate_transforms(&fdf);
	print_points(&fdf);
	free(fdf.points);
}
