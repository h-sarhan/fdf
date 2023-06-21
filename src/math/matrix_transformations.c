/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:22 by mkhan             #+#    #+#             */
/*   Updated: 2023/06/21 10:07:43 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Sets the matrix to the identity matrix
 * @param mat The matrix to be set to an identity matrix
 */
void identity_matrix(t_mat4 mat)
{
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[0][3] = 0;
    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = 0;
    mat[1][3] = 0;
    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
    mat[2][3] = 0;
    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

/**
 * @brief Initialize the translation matrix.
 * @param mat Matrix to be initialized.
 * @param x The value along the x-axis to be translated.
 * @param y The value along the y-axis to be translated.
 * @param z The value along the z-axis to be translated.
 */
void translate_matrix(t_mat4 mat, float x, float y, float z)
{
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[0][3] = x;

    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = 0;
    mat[1][3] = y;

    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
    mat[2][3] = z;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

/**
 * @brief Initialize the scaling matrix
 * @param mat The matrix to be initialized
 * @param x The value along the x-axis to be scaled.
 * @param y The value along the y-axis to be scaled.
 * @param z The value along the z-axis to be scaled.
 */
void scaling_matrix(t_mat4 mat, float x, float y, float z)
{
    mat[0][0] = x;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[0][3] = 0;

    mat[1][0] = 0;
    mat[1][1] = y;
    mat[1][2] = 0;
    mat[1][3] = 0;

    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = z;
    mat[2][3] = 0;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

/**
 * @brief Initialize the matrix for rotation along x-axis
 * @param mat The matrix to be initialized
 * @param r angle in radians
 */
void rotation_matrix_x(t_mat4 mat, float r)
{
    float c;
    float s;

    c = cosf(r);
    s = sinf(r);

    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[0][3] = 0;

    mat[1][0] = 0;
    mat[1][1] = c;
    mat[1][2] = -s;
    mat[1][3] = 0;

    mat[2][0] = 0;
    mat[2][1] = s;
    mat[2][2] = c;
    mat[2][3] = 0;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

/**
 * @brief Initialize the matrix for rotation along y-axis
 * @param mat The matrix to be initialized
 * @param r angle in radians
 */
void rotation_matrix_y(t_mat4 mat, float r)
{
    float c;
    float s;

    c = cosf(r);
    s = sinf(r);

    mat[0][0] = c;
    mat[0][1] = 0;
    mat[0][2] = s;
    mat[0][3] = 0;

    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = 0;
    mat[1][3] = 0;

    mat[2][0] = -s;
    mat[2][1] = 0;
    mat[2][2] = c;
    mat[2][3] = 0;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

/**
 * @brief Initialize the matrix for rotation along z-axis
 * @param mat The matrix to be initialized
 * @param r angle in radians
 */
void rotation_matrix_z(t_mat4 mat, float r)
{
    float c;
    float s;

    c = cosf(r);
    s = sinf(r);

    mat[0][0] = c;
    mat[0][1] = -s;
    mat[0][2] = 0;
    mat[0][3] = 0;

    mat[1][0] = s;
    mat[1][1] = c;
    mat[1][2] = 0;
    mat[1][3] = 0;

    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
    mat[2][3] = 0;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

void calculate_transforms(t_fdf *fdf)
{
    t_mat4 scale_mat;

    identity_matrix(fdf->transform_mat);
    scaling_matrix(scale_mat, fdf->scale, fdf->scale, fdf->scale);
    mat_multiply(fdf->transform_mat, scale_mat, fdf->transform_mat);
    mat_multiply(fdf->transform_mat, fdf->orientation, fdf->transform_mat);
    mat_multiply(fdf->transform_mat, fdf->translation, fdf->transform_mat);
    mat_multiply(fdf->transform_mat, fdf->projection, fdf->transform_mat);
}
