/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:22 by mkhan             #+#    #+#             */
/*   Updated: 2022/12/28 20:10:48 by hsarhan          ###   ########.fr       */
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

void	cross_product(t_vector *res, const t_vector *v1, const t_vector *v2)
{
	res->x = v1->y * v2->z - v1->z * v2->y;
	res->y = v1->z * v2->x - v1->x * v2->z;
	res->z = v1->x * v2->y - v1->y * v2->x;
}

void	view_transform(t_mat4 *res, const t_vector *from, const t_vector *up)
{
	t_vector	left;
	t_vector	true_up;
	t_vector	upn;
	t_mat4		orientation;
	t_mat4		translation;
	t_vector	forward;

	ft_memcpy(&upn, up, sizeof(t_vector));
	normalize_vec(&upn);
	forward.x = 0;
	forward.y = 0;
	forward.z = 1;
	cross_product(&left, &forward, &upn);
	normalize_vec(&left);
	cross_product(&true_up, &left, &forward);
	normalize_vec(&true_up);
	ft_bzero(&orientation, sizeof(t_mat4));
	orientation[0][0] = left.x;
	orientation[0][1] = left.y;
	orientation[0][2] = left.z;
	orientation[1][0] = true_up.x;
	orientation[1][1] = true_up.y;
	orientation[1][2] = true_up.z;
	orientation[2][0] = forward.x * -1;
	orientation[2][1] = forward.y * -1;
	orientation[2][2] = forward.z * -1;
	orientation[3][3] = 1;
	translate_matrix(&translation, from->x * -1, from->y * -1, from->z * -1);
	mat_multiply(res, &orientation, &translation);
}

void	calculate_camera_transform(t_fdf *fdf)
{
	t_vector		from;
	t_vector		up;

	from.x = 0;
	from.y = 0;
	from.z = -1;
	from.w = 1;
	up.x = 0;
	up.y = 1;
	up.z = 0;
	up.w = 0;
	view_transform(&fdf->cam_transform, &from, &up);
}


void	calculate_transforms(t_fdf *fdf)
{
	t_mat4	scale_mat;
	t_mat4	translate_origin;
	t_mat4	projection;

	identity_matrix(&fdf->transform_mat);
	translate_matrix(&translate_origin, -fdf->max_x / 2.0, -fdf->max_y / 2.0, 0);
	mat_multiply(&fdf->transform_mat, &translate_origin, &fdf->transform_mat);
	scaling_matrix(&scale_mat, fdf->scale, fdf->scale, fdf->scale);
	
	mat_multiply(&fdf->transform_mat, &scale_mat, &fdf->transform_mat);
	mat_multiply(&fdf->transform_mat, &fdf->orientation, &fdf->transform_mat);
	mat_multiply(&fdf->transform_mat, &fdf->translation, &fdf->transform_mat);
}