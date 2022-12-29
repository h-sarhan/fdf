/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:58:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/30 03:44:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO: NDC Coordinates
// TODO: perspective projection
// TODO: THICK lines
// TODO: Hidden line removal

void	draw_points(t_fdf *fdf)
{
	t_vector	point;
	t_vector	res;

	int	idx;
	short		*xys;
	idx = 0;
	xys = malloc(sizeof(short) * 2 * fdf->point_count);
	if (xys == NULL)
		exit(17);
	for (int i = 0; i < fdf->max_y; i++)
	{
		for (int j = 0; j < fdf->max_x; j++)	
		{
			point.x = j;
			point.y = i;
			point.z = fdf->points[i * fdf->max_x + j].height;
			mat_vec_multiply(&res, &fdf->transform_mat, &point);
			// fdf->points[i * fdf->max_x + j].x = res.x;
			// fdf->points[i * fdf->max_x + j].y = res.y;
			xys[idx] = res.x;
			xys[idx + 1] = res.y;
			idx += 2;
		}
	}
	for (int i = 0; i < fdf->max_y; i++)
	{
		for (int j = 0; j < fdf->max_x; j++)	
		{
			int c1 = fdf->colors[fdf->points[i * fdf->max_x + j].color_idx];
			if (j + 1 < fdf->max_x)
			{
				int c2 = fdf->colors[fdf->points[i * fdf->max_x + j + 1].color_idx];
				dda(fdf, xys[i * fdf->max_x * 2 + j * 2], xys[i * fdf->max_x * 2 + (j + 1) * 2],
					xys[i * fdf->max_x * 2 + j * 2 + 1], xys[i * fdf->max_x * 2 + (j + 1) * 2 + 1], c1, c2);
				// dda(fdf, fdf->points[i * fdf->max_x + j].x, fdf->points[i * fdf->max_x + j + 1].x, 
				// 	fdf->points[i * fdf->max_x + j].y, fdf->points[i * fdf->max_x + j + 1].y, c1, c2);
			}
			if (i + 1 < fdf->max_y)
			{
				int c2 = fdf->colors[fdf->points[(i + 1) * fdf->max_x + j].color_idx];
				dda(fdf, xys[i * fdf->max_x * 2 + j * 2], xys[(i + 1) * fdf->max_x * 2 + (j) * 2],
					xys[i * fdf->max_x * 2 + j * 2 + 1], xys[(i + 1) * fdf->max_x * 2 + (j) * 2 + 1], c1, c2);
				// dda(fdf, fdf->points[i * fdf->max_x + j].x, fdf->points[(i + 1) * fdf->max_x + j].x, 
				// 	fdf->points[i * fdf->max_x + j].y, fdf->points[(i + 1) * fdf->max_x + j].y, c1, c2);
			}
		}
	}
	free(xys);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
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
	fdf.max_y = fdf.point_count / fdf.max_x;
	if (fdf.points == NULL)
		exit(!printf("FAILED TO MALLOC\n"));
	close(fd);
	// fdf.scale = fdf.max;
	fdf.scale = 2;
	resize_points(&fdf, fdf.point_count);
	identity_matrix(&fdf.orientation);
	translate_matrix(&fdf.translation, SCREEN_W / 2.0 , SCREEN_H / 2.0, 0);
	
	t_mat4	projection;	
	identity_matrix(&projection);
	rotation_matrix_z(&projection, -45 * DEG_TO_RAD);
	mat_multiply(&fdf.orientation, &projection, &fdf.orientation);
	rotation_matrix_x(&projection, 35.264 * DEG_TO_RAD);
	mat_multiply(&fdf.orientation, &projection, &fdf.orientation);

	calculate_transforms(&fdf);
	fdf.mlx = mlx_init();
	if (fdf.mlx == NULL)
		printf("OOPS\n");
	fdf.win = mlx_new_window(fdf.mlx, SCREEN_W, SCREEN_H, "FDF"); 
	fdf.img = mlx_new_image(fdf.mlx, SCREEN_W, SCREEN_H);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_size, &fdf.endian);
	fdf.bpp /= 8;
	// fdf.img2 = mlx_new_image(fdf.mlx, SCREEN_W, SCREEN_H);
	// fdf.addr2 = mlx_get_data_addr(fdf.img2, &fdf.bpp, &fdf.line_size, &fdf.endian);
	// fdf.bpp /= 8;
	
	draw_points(&fdf);
	mlx_hook(fdf.win, 2, (1L << 0), key_press, &fdf);
	mlx_hook(fdf.win, 3, (1L << 1), key_release, &fdf);
	mlx_loop_hook(fdf.mlx, render_loop, &fdf);
	mlx_loop(fdf.mlx);
	free(fdf.points);
}
