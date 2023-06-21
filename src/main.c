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

    for (int i = 0; i < fdf->max_y; i++)
    {
        for (int j = 0; j < fdf->max_x; j++)
        {
            point[0] = j - fdf->max_x / 2.0f;
            point[1] = i - fdf->max_y / 2.0f;
            point[2] = fdf->points[i * fdf->max_x + j].height;
            point[3] = 1;
            mat_vec_multiply(&res, &fdf->transform_mat, &point);
            xys[idx] = res[0];
            xys[idx + 1] = res[1];
            idx += 2;
        }
    }
    for (int i = 0; i < fdf->max_y; i++)
    {
        for (int j = 0; j < fdf->max_x - 1; j++)
        {
            int c1 = fdf->points[i * fdf->max_x + j].color;
            int c2 = fdf->points[i * fdf->max_x + j + 1].color;
            draw_line(fdf, xys[i * fdf->max_x * 2 + j * 2],
                      xys[i * fdf->max_x * 2 + (j + 1) * 2],
                      xys[i * fdf->max_x * 2 + j * 2 + 1],
                      xys[i * fdf->max_x * 2 + (j + 1) * 2 + 1], c1, c2);
        }
    }
    for (int i = 0; i < fdf->max_y - 1; i++)
    {
        for (int j = 0; j < fdf->max_x; j++)
        {
            int c1 = fdf->points[i * fdf->max_x + j].color;
            int c2 = fdf->points[(i + 1) * fdf->max_x + j].color;
            draw_line(fdf, xys[i * fdf->max_x * 2 + j * 2],
                      xys[(i + 1) * fdf->max_x * 2 + (j) *2],
                      xys[i * fdf->max_x * 2 + j * 2 + 1],
                      xys[(i + 1) * fdf->max_x * 2 + (j) *2 + 1], c1, c2);
        }
    }
    free(xys);
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void center_to_world(t_fdf *fdf)
{
    t_vec4 screen_center = {(float) SCREEN_W / 2, (float) SCREEN_H / 2, 0};
    t_vec4 world_center;
    mat_vec_multiply(&world_center, &fdf->inv_projection, &screen_center);
    translate_matrix(&fdf->translation, world_center[0], world_center[1], 0);
}

void fit_to_width(t_fdf *fdf)
{
    t_vec4 screen_edge = {(float) SCREEN_W - 1, 0, 0};
    t_vec4 world_screen_edge;
    mat_vec_multiply(&world_screen_edge, &fdf->inv_projection, &screen_edge);
    fdf->scale = world_screen_edge[0] / ((float) fdf->max_x);
    fdf->scale *= 0.7;
}

int main(int argc, char **argv)
{
    t_fdf *fdf;
    int fd;

    fdf = ft_calloc(1, sizeof(t_fdf));
    if (!fdf)
        exit(1);
    // fdf->cam_pos[0] = 100;
    fdf->cam_pos[3] = 1;

    fdf->cam_look[0] = 0;
    fdf->cam_look[1] = 0;
    fdf->cam_look[2] = -1;
    printf("fdf->cam_pos[0] = %f\n", fdf->cam_pos[0]);
    fdf->max_size = MAX_POINT_COUNT;
    fdf->max_z = INT16_MIN;
    fdf->min_z = INT16_MAX;
    // fdf->colors[0] = 0xffffff;
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

    fdf->points = malloc(MAX_POINT_COUNT * sizeof(t_point));
    if (fdf->points == NULL)
        exit(!printf("FAILED TO MALLOC\n"));
    parse_map(fdf, fd);
    fdf->max_y = fdf->point_count / fdf->max_x;
    if (fdf->points == NULL)
        exit(!printf("FAILED TO MALLOC\n"));
    close(fd);
    // fdf->scale = fdf->max;
    // fdf->scale = 0.7;
    resize_points(fdf, fdf->point_count);
    identity_matrix(&fdf->orientation);
    identity_matrix(&fdf->translation);
    rotation_matrix_x(&fdf->orientation, 30 * DEG_TO_RAD);

    fdf->scale = 1;
    // fdf->cam_theta =
    //     atan2(fdf->cam_look[2] / fdf->cam_look[0], fdf->cam_look[0]);
    // fdf->cam_phi = acos(fdf->cam_look[1]);
    // sphere_to_xyz(&fdf->cam_look, fdf->cam_phi, fdf->cam_theta, 1);
    calculate_transforms(fdf);
    // center_to_world(fdf);
    // fit_to_width(fdf);
    // calculate_transforms(fdf);

    fdf->mlx = mlx_init();
    if (fdf->mlx == NULL)
    {
        printf("OOPS\n");
        exit(1);
    }
    fdf->win = mlx_new_window(fdf->mlx, SCREEN_W, SCREEN_H, "FDF");
    fdf->img = mlx_new_image(fdf->mlx, SCREEN_W, SCREEN_H);
    fdf->addr =
        mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->line_size, &fdf->endian);

    draw_points(fdf);
    mlx_hook(fdf->win, 2, (1L << 0), key_press, fdf);
    mlx_hook(fdf->win, 3, (1L << 1), key_release, fdf);
    mlx_loop_hook(fdf->mlx, render_loop, fdf);
    mlx_loop(fdf->mlx);
    // free(fdf->points);
}
