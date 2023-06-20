/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:30:05 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/20 19:50:29 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void toggle_keys_held(int key, t_fdf *fdf, bool on_off)
{
    if (key == KEY_W)
        fdf->keys.w = on_off;
    if (key == KEY_A)
        fdf->keys.a = on_off;
    if (key == KEY_S)
        fdf->keys.s = on_off;
    if (key == KEY_D)
        fdf->keys.d = on_off;
    if (key == KEY_UP)
        fdf->keys.up = on_off;
    if (key == KEY_DOWN)
        fdf->keys.down = on_off;
    if (key == KEY_LEFT)
        fdf->keys.left = on_off;
    if (key == KEY_RIGHT)
        fdf->keys.right = on_off;
    if (key == KEY_Q)
        fdf->keys.q = on_off;
    if (key == KEY_E)
        fdf->keys.e = on_off;
    if (key == KEY_PLUS)
        fdf->keys.plus = on_off;
    if (key == KEY_MINUS)
        fdf->keys.minus = on_off;
    if (key == KEY_SHIFT)
        fdf->keys.shift = on_off;
    if (key == KEY_X)
        fdf->keys.x = on_off;
    if (key == KEY_Y)
        fdf->keys.y = on_off;
    if (key == KEY_Z)
        fdf->keys.z = on_off;
}

int close_window(t_fdf *fdf)
{
    printf("QUITTING PROGRAM!\n");
    mlx_destroy_image(fdf->mlx, fdf->img);
    // mlx_destroy_window(fdf->mlx, fdf->win);
    // mlx_destroy_display(fdf->mlx);
    free(fdf->mlx);
    exit(EXIT_SUCCESS);
    return (0);
}

int key_press(int key, t_fdf *fdf)
{
    toggle_keys_held(key, fdf, true);
    if (key == KEY_ESC)
    {
        close_window(fdf);
    }
    return (0);
}

int key_release(int key, t_fdf *fdf)
{
    toggle_keys_held(key, fdf, false);
    return (0);
}

int render_loop(t_fdf *fdf)
{
    t_mat4 mat;
    if (fdf->keys.plus == true)
        fdf->scale += ZOOM_SPEED;
    if (fdf->keys.minus == true)
    {
        if (fdf->scale > 0.1)
            fdf->scale -= ZOOM_SPEED;
    }
    if (fdf->keys.w == true)
    {
        translate_matrix(mat, 0, -MOVE_SPEED, 0);
        mat_multiply(fdf->translation, mat, fdf->translation);
    }
    if (fdf->keys.s == true)
    {
        translate_matrix(mat, 0, MOVE_SPEED, 0);
        mat_multiply(fdf->translation, mat, fdf->translation);
    }
    if (fdf->keys.q == true)
    {
        translate_matrix(mat, 0, 0, MOVE_SPEED);
        mat_multiply(fdf->translation, mat, fdf->translation);
    }
    if (fdf->keys.e == true)
    {
        translate_matrix(mat, 0, 0, -MOVE_SPEED);
        mat_multiply(fdf->translation, mat, fdf->translation);
    }
    if (fdf->keys.a == true)
    {
        translate_matrix(mat, -MOVE_SPEED, 0, 0);
        mat_multiply(fdf->translation, mat, fdf->translation);
    }
    if (fdf->keys.d == true)
    {
        translate_matrix(mat, MOVE_SPEED, 0, 0);
        mat_multiply(fdf->translation, mat, fdf->translation);
    }
    if (fdf->keys.right == true)
    {
        rotation_matrix_y(mat, ROT_SPEED * DEG_TO_RAD);
        mat_multiply(fdf->orientation, mat, fdf->orientation);
    }
    if (fdf->keys.left == true)
    {
        rotation_matrix_y(mat, -ROT_SPEED * DEG_TO_RAD);
        mat_multiply(fdf->orientation, mat, fdf->orientation);
    }
    if (fdf->keys.up == true)
    {
        rotation_matrix_x(mat, ROT_SPEED * DEG_TO_RAD);
        mat_multiply(fdf->orientation, mat, fdf->orientation);
    }
    if (fdf->keys.down == true)
    {
        rotation_matrix_x(mat, -ROT_SPEED * DEG_TO_RAD);
        mat_multiply(fdf->orientation, mat, fdf->orientation);
    }
    if (fdf->keys.w || fdf->keys.a || fdf->keys.s || fdf->keys.d ||
        fdf->keys.left || fdf->keys.right || fdf->keys.up || fdf->keys.down ||
        fdf->keys.minus || fdf->keys.plus || fdf->keys.q || fdf->keys.e)
    {
        bzero(fdf->addr, SCREEN_H * SCREEN_W * fdf->bpp);
        calculate_transforms(fdf);
        draw_points(fdf);
    }
    return (0);
}
