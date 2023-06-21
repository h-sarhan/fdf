/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:58:05 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/21 10:57:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO: Perspective projection
// TODO: Proper view projection and orthographic projection matrices
// TODO: Camera

// TODO: .OBJ files

// TODO: THICK Anti-aliased lines
// https://github.com/jambolo/thick-xiaolin-wu/blob/master/cs/thick-xiaolin-wu.coffee

// ! HARD
// TODO: Conical projection
// TODO: Hidden line removal
// TODO: Multi threading
// TODO: Triangles
// TODO: Backface culling
// TODO: Z-buffer

void draw_points(t_fdf *fdf)
{
    t_vec4 point;
    t_vec4 res;

    int idx;
    short *xys;
    idx = 0;
    // printf("z_min == %d\n", fdf->min_z);
    // printf("z_max == %d\n", fdf->max_z);
    xys = malloc(sizeof(short) * 2 * fdf->point_count);
    if (xys == NULL)
        exit(17);
    t_mat4 vp_mat;
    viewport_projection(vp_mat);

    t_mat4 orth_mat;
    orthographic_projection(orth_mat);

    t_mat4 projection;
    mat_multiply(projection, vp_mat, orth_mat);
    for (int i = 0; i < fdf->max_y; i++)
    {
        for (int j = 0; j < fdf->max_x; j++)
        {
            point[0] = j - fdf->max_x / 2.0f;
            point[1] = i - fdf->max_y / 2.0f;

            int16_t height = fdf->points[i * fdf->max_x + j].height;
            point[2] = height;
            point[3] = 1;

            t_vec4 proj_point;
            mat_vec_multiply(res, fdf->transform_mat, point);
            mat_vec_multiply(proj_point, projection, res);
            xys[idx] = (proj_point[0]);
            xys[idx + 1] = (proj_point[1]);

            idx += 2;
        }
    }
    for (int i = 0; i < fdf->max_y; i++)
    {
        for (int j = 0; j < fdf->max_x; j++)
        {
            // t_vec4 p1 = {2, 1, 1, 1};
            // t_vec4 p2 = {2, 1, 1, 1};
            int c1 = fdf->points[i * fdf->max_x + j].color;
            if (j + 1 < fdf->max_x)
            {
                int c2 = fdf->points[i * fdf->max_x + j + 1].color;
                draw_line(fdf, xys[i * fdf->max_x * 2 + j * 2],
                          xys[i * fdf->max_x * 2 + (j + 1) * 2],
                          xys[i * fdf->max_x * 2 + j * 2 + 1],
                          xys[i * fdf->max_x * 2 + (j + 1) * 2 + 1], c1, c2);
            }
            if (i + 1 < fdf->max_y)
            {
                int c2 = fdf->points[(i + 1) * fdf->max_x + j].color;
                draw_line(fdf, xys[i * fdf->max_x * 2 + j * 2],
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
    // translate_matrix(fdf.translation, (float) fdf.max_x / 2,
    //                  (float) fdf.max_y / 2, 0);

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
