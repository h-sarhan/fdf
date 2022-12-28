/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:58:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 20:47:12 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(int x, int y, int color, t_fdf *fdf)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_W || y >= SCREEN_H)
		return ;
	dst = fdf->addr + (y * fdf->line_size + x * fdf->bpp);
	*(unsigned int *)dst = color;
}

void	draw_points(t_fdf *fdf)
{
	t_vector	vec;
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;

	ft_bzero(fdf->addr, SCREEN_H * SCREEN_W * fdf->bpp);
	for (int i = 0; i < fdf->max_y; i++)
	{
		for (int j = 0; j < fdf->max_x - 1; j++)
		{
			vec.x = j;
			vec.y = i;
			vec.z = fdf->points[i * fdf->max_x + j].height;
			vec.w = 1;
			mat_vec_multiply(&p1, &fdf->transform_mat, &vec);
			vec.x = j + 1;
			vec.y = i;
			vec.z = fdf->points[i * fdf->max_x + j + 1].height;
			vec.w = 1;
			mat_vec_multiply(&p2, &fdf->transform_mat, &vec);
			int color = fdf->points[i * fdf->max_x + j + 1].color_idx;
			color = fdf->colors[color];
			dda(fdf, p1.x, p2.x, p1.y, p2.y, color);
		}
	}
	for (int i = 0; i < fdf->max_y - 1; i++)
	{
		for (int j = 0; j < fdf->max_x; j++)
		{
			vec.x = j;
			vec.y = i;
			vec.z = fdf->points[i * fdf->max_x + j].height;
			vec.w = 1;
			mat_vec_multiply(&p1, &fdf->transform_mat, &vec);
			vec.x = j;
			vec.y = i + 1;
			vec.z = fdf->points[(i + 1) * fdf->max_x + j].height;
			vec.w = 1;
			mat_vec_multiply(&p2, &fdf->transform_mat, &vec);
			int color = fdf->points[i * fdf->max_x + j + 1].color_idx;
			color = fdf->colors[color];
			dda(fdf, p1.x, p2.x, p1.y, p2.y, color);
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	ft_memcpy(fdf->addr2, fdf->addr, SCREEN_H * SCREEN_W * fdf->bpp);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img2, 0, 0);
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
	translate_matrix(&fdf.translation, SCREEN_W / 2 , SCREEN_H / 2, 0);
	
	t_mat4	projection;	
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
	fdf.img2 = mlx_new_image(fdf.mlx, SCREEN_W, SCREEN_H);
	fdf.addr2 = mlx_get_data_addr(fdf.img2, &fdf.bpp, &fdf.line_size, &fdf.endian);
	fdf.bpp /= 8;
	
	draw_points(&fdf);
	mlx_hook(fdf.win, 2, (1L << 0), key_press, &fdf);
	mlx_hook(fdf.win, 3, (1L << 1), key_release, &fdf);
	mlx_loop_hook(fdf.mlx, render_loop, &fdf);
	mlx_loop(fdf.mlx);
	free(fdf.points);
}
