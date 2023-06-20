/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:58:05 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/20 20:05:06 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO: Implement line clipping algorithm
// TODO: Multi threading
// TODO: Camera
// TODO: .OBJ files
// TODO: THICK lines
// TODO: Anti-aliased lines
// TODO: Proper view projection and orthographic projection matrices
// Page 162 Fundamentals of computer graphics
// TODO: Fix color gradient
// 1: https://github.com/VBrazhnik/FdF/wiki/How-to-create-linear-gradient%3F
// 2: https://stackoverflow.com/questions/22607043/color-gradient-algorithm
// TODO: Perspective projection
// TODO: Conical projection
// TODO: Hidden line removal

void draw_points(t_fdf *fdf)
{
    t_vector point;
    t_vector res;

    int idx;
    short *xys;
    idx = 0;
    // printf("z_min == %d\n", fdf->min_z);
    // printf("z_max == %d\n", fdf->max_z);
    xys = malloc(sizeof(short) * 2 * fdf->point_count);
    if (xys == NULL)
        exit(17);
    for (int i = 0; i < fdf->max_y; i++)
    {
        for (int j = 0; j < fdf->max_x; j++)
        {
            point[0] = (2.0f * j / fdf->max_x - 1.0f);
            point[1] = (2.0f * i / fdf->max_y - 1.0f);
            int16_t height = fdf->points[i * fdf->max_x + j].height;

            point[2] =
                (height - fdf->min_z) / (float) (fdf->max_z - fdf->min_z);

            mat_vec_multiply(res, fdf->transform_mat, point);
            xys[idx] = (res[0]) * SCREEN_W / 2.0f;
            xys[idx + 1] = (res[1]) * SCREEN_H / 2.0f;

            idx += 2;
        }
    }
    for (int i = 0; i < fdf->max_y; i++)
    {
        for (int j = 0; j < fdf->max_x; j++)
        {
            int c1 = fdf->points[i * fdf->max_x + j].color;
            if (j + 1 < fdf->max_x)
            {
                int c2 = fdf->points[i * fdf->max_x + j + 1].color;
                dda(fdf, xys[i * fdf->max_x * 2 + j * 2],
                    xys[i * fdf->max_x * 2 + (j + 1) * 2],
                    xys[i * fdf->max_x * 2 + j * 2 + 1],
                    xys[i * fdf->max_x * 2 + (j + 1) * 2 + 1], c1, c2);
            }
            if (i + 1 < fdf->max_y)
            {
                int c2 = fdf->points[(i + 1) * fdf->max_x + j].color;
                dda(fdf, xys[i * fdf->max_x * 2 + j * 2],
                    xys[(i + 1) * fdf->max_x * 2 + (j) *2],
                    xys[i * fdf->max_x * 2 + j * 2 + 1],
                    xys[(i + 1) * fdf->max_x * 2 + (j) *2 + 1], c1, c2);
            }
        }
    }
    free(xys);
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

int main(int argc, char **argv)
{
    t_fdf fdf;
    int fd;

    ft_bzero(&fdf, sizeof(t_fdf));
    fdf.max_size = MAX_POINT_COUNT;
    fdf.max_z = INT16_MIN;
    fdf.min_z = INT16_MAX;
    // fdf.colors[0] = 0xffffff;
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
    fdf.scale = 0.7;
    resize_points(&fdf, fdf.point_count);
    identity_matrix(fdf.orientation);
    translate_matrix(fdf.translation, 1, 1, 0);
    // translate_matrix(fdf.translation, 0, 0, 0);

    t_mat4 projection;
    identity_matrix(projection);
    rotation_matrix_z(projection, -45 * DEG_TO_RAD);
    mat_multiply(fdf.orientation, projection, fdf.orientation);
    rotation_matrix_x(projection, 35.264 * DEG_TO_RAD);
    mat_multiply(fdf.orientation, projection, fdf.orientation);

    calculate_transforms(&fdf);
    fdf.mlx = mlx_init();
    if (fdf.mlx == NULL)
        printf("OOPS\n");
    fdf.win = mlx_new_window(fdf.mlx, SCREEN_W, SCREEN_H, "FDF");
    fdf.img = mlx_new_image(fdf.mlx, SCREEN_W, SCREEN_H);
    fdf.addr =
        mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.line_size, &fdf.endian);
    fdf.bpp /= 8;

    draw_points(&fdf);
    mlx_hook(fdf.win, 2, (1L << 0), key_press, &fdf);
    mlx_hook(fdf.win, 3, (1L << 1), key_release, &fdf);
    mlx_loop_hook(fdf.mlx, render_loop, &fdf);
    mlx_loop(fdf.mlx);
    free(fdf.points);
}
