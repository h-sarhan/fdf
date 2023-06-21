/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:07:06 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/21 10:50:50 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void viewport_projection(t_mat4 *res)
{
    (*res)[0][0] = SCREEN_W / 2.0f;
    (*res)[0][1] = 0;
    (*res)[0][2] = 0;
    (*res)[0][3] = 0;

    (*res)[1][0] = 0;
    (*res)[1][1] = SCREEN_H / 2.0f;
    (*res)[1][2] = 0;
    (*res)[1][3] = 0;

    (*res)[2][0] = 0;
    (*res)[2][1] = 0;
    (*res)[2][2] = 1;
    (*res)[2][3] = 0;

    (*res)[3][0] = (SCREEN_W - 1) / 2.0f;
    (*res)[3][1] = (SCREEN_H - 1) / 2.0f;
    (*res)[3][2] = 0;
    (*res)[3][3] = 1;
}

void orthographic_projection(t_mat4 *res)
{
    const float n = 1.0f;
    float f = 10.0f;
    float t = tan(60 * DEG_TO_RAD / 2) * n;
    float r = (SCREEN_W / (float) SCREEN_H) * t;
    float l = -r;
    float b = -t;

    (*res)[0][0] = 2 / (r - l);
    (*res)[0][1] = 0;
    (*res)[0][2] = 0;
    (*res)[0][3] = 0;

    (*res)[1][0] = 0;
    (*res)[1][1] = 2 / (t - b);
    (*res)[1][2] = 0;
    (*res)[1][3] = 0;

    (*res)[2][0] = 0;
    (*res)[2][1] = 0;
    (*res)[2][2] = 2 / (n - f);
    (*res)[2][3] = 0;

    (*res)[3][0] = -(r + l) / (r - l);
    (*res)[3][1] = -(t + b) / (t - b);
    (*res)[3][2] = -(n + f) / (n - f);
    (*res)[3][3] = 1;
}

void camera_projection(t_mat4 *res, t_vec4 *origin, t_vec4 *up, t_vec4 *look)
{
    t_vec4 u;
    t_vec4 v;
    t_vec4 w;

    normalize_vec(look);
    normalize_vec(up);

    negate_vec(&w, look);

    cross_product(&u, up, &w);
    normalize_vec(&u);

    cross_product(&v, &w, &u);
    normalize_vec(&v);

    t_mat4 proj_inv;

    proj_inv[0][0] = u[0];
    proj_inv[0][1] = v[0];
    proj_inv[0][2] = w[0];
    proj_inv[0][3] = (*origin)[0];

    proj_inv[1][0] = u[1];
    proj_inv[1][1] = v[1];
    proj_inv[1][2] = w[1];
    proj_inv[1][3] = (*origin)[1];

    proj_inv[2][0] = u[2];
    proj_inv[2][1] = v[2];
    proj_inv[2][2] = w[2];
    proj_inv[2][3] = (*origin)[2];

    proj_inv[3][0] = 0;
    proj_inv[3][1] = 0;
    proj_inv[3][2] = 0;
    proj_inv[3][3] = 1;

    mat_inverse(res, &proj_inv);
}

void sphere_to_xyz(t_vec4 *vec, double phi, double theta, double r)
{
    (*vec)[0] = r * sin(phi) * cos(theta);
    (*vec)[1] = r * sin(phi) * sin(theta);
    (*vec)[2] = r * cos(phi);
    (*vec)[3] = 0;
}