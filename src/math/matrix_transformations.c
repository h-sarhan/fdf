/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:22 by mkhan             #+#    #+#             */
/*   Updated: 2022/12/28 16:24:35 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Initialize the translation matrix.
 * @param mat Matrix to be initialized.
 * @param x The value along the x-axis to be translated.
 * @param y The value along the y-axis to be translated.
 * @param z The value along the z-axis to be translated.
 */
void	translate_matrix(t_mat4 *mat, float x, float y, float z)
{
	ft_bzero(mat, sizeof(t_mat4));
	(*mat)[0][0] = 1;
	(*mat)[1][1] = 1;
	(*mat)[2][2] = 1;
	(*mat)[3][3] = 1;
	(*mat)[0][3] = x;
	(*mat)[1][3] = y;
	(*mat)[2][3] = z;
}

/**
 * @brief Initialize the scaling matrix
 * @param mat The matrix to be initialized
 * @param x The value along the x-axis to be scaled.
 * @param y The value along the y-axis to be scaled.
 * @param z The value along the z-axis to be scaled.
 */
void	scaling_matrix(t_mat4 *mat, float x, float y, float z)
{
	ft_bzero(mat, sizeof(t_mat4));
	(*mat)[0][0] = x;
	(*mat)[1][1] = y;
	(*mat)[2][2] = z;
	(*mat)[3][3] = 1;
}

/**
 * @brief Initialize the matrix for rotation along x-axis
 * @param mat The matrix to be initialized
 * @param r angle in radians
 */
void	rotation_matrix_x(t_mat4 *mat, float r)
{
	float	c;
	float	s;

	ft_bzero(mat, sizeof(t_mat4));
	c = cosf(r);
	s = sinf(r);
	(*mat)[0][0] = 1;
	(*mat)[1][1] = c;
	(*mat)[1][2] = -s;
	(*mat)[2][1] = s;
	(*mat)[2][2] = c;
	(*mat)[3][3] = 1;
}

/**
 * @brief Initialize the matrix for rotation along y-axis
 * @param mat The matrix to be initialized
 * @param r angle in radians
 */
void	rotation_matrix_y(t_mat4 *mat, float r)
{
	float	c;
	float	s;

	ft_bzero(mat, sizeof(t_mat4));
	c = cosf(r);
	s = sinf(r);
	(*mat)[0][0] = c;
	(*mat)[0][2] = s;
	(*mat)[1][1] = 1;
	(*mat)[2][0] = -s;
	(*mat)[2][2] = c;
	(*mat)[3][3] = 1;
}

/**
 * @brief Initialize the matrix for rotation along z-axis
 * @param mat The matrix to be initialized
 * @param r angle in radians
 */
void	rotation_matrix_z(t_mat4 *mat, float r)
{
	float	c;
	float	s;

	ft_bzero(mat, sizeof(t_mat4));
	c = cosf(r);
	s = sinf(r);
	(*mat)[0][0] = c;
	(*mat)[0][1] = -s;
	(*mat)[1][0] = s;
	(*mat)[1][1] = c;
	(*mat)[2][2] = 1;
	(*mat)[3][3] = 1;
}


void	calculate_transforms(t_fdf *fdf)
{
	t_mat4	scale_mat;
	t_mat4	translate_origin;
	// t_mat4	identity;

	translate_matrix(&translate_origin, -fdf->max_x / 2.0, -fdf->max_y / 2.0, 0);
	scaling_matrix(&scale_mat, fdf->scale, fdf->scale, fdf->scale);
	// identity_matrix(&scale_mat);
	mat_multiply(&fdf->transform_mat, &scale_mat, &translate_origin);
	translate_matrix(&translate_origin, fdf->max_x * fdf->scale / 2.0, fdf->max_y * fdf->scale / 2.0, 0);
	mat_multiply(&fdf->transform_mat, &translate_origin, &fdf->transform_mat);
}