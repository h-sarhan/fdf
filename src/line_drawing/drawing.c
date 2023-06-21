/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:08:48 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/21 09:48:41 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Get the red part of a color
int get_r(int trgb)
{
    return ((trgb >> 16) & 0xFF);
}

// Get the green part of a color
int get_g(int trgb)
{
    return ((trgb >> 8) & 0xFF);
}

// Get the blue part of a color
int get_b(int trgb)
{
    return (trgb & 0xFF);
}

void draw_line(t_fdf *fdf, float x1, float x2, float y1, float y2, int c1,
               int c2)
{
    float dy;
    float dx;
    float steps;

    if (!clip_line(&x1, &y1, &x2, &y2))
        return;
    dx = (x2 - x1);
    dy = (y2 - y1);
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    if (fabs(steps) < 0.001)
        return;
    dx /= steps;
    dy /= steps;

    int r = get_r(c1);
    int g = get_g(c1);
    int b = get_b(c1);
    int dr = (-r + get_r(c2)) / (float) steps;
    int dg = (-g + get_g(c2)) / (float) steps;
    int db = (-b + get_b(c2)) / (float) steps;

    r <<= 16;
    g <<= 8;
    dr <<= 16;
    dg <<= 8;
    while (steps > 0)
    {
        *(unsigned int *) (fdf->addr + (int) ((int) y1 * fdf->line_size +
                                              (int) x1 * fdf->bpp / 8)) =
            r | g | b;
        y1 += dy;
        x1 += dx;
        r += dr;
        g += dg;
        b += db;
        steps--;
    }
}
