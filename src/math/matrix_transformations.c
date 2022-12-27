/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:22 by mkhan             #+#    #+#             */
/*   Updated: 2022/12/28 01:04:03 by hsarhan          ###   ########.fr       */
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

/**
 * @brief Convert Radians to Degrees
 * @param r The radian value
 * @return float The converted value in degrees
 */
float	rad_to_deg(float r)
{
	return (r * RAD_TO_DEG);
}

/**
 * @brief Convert Degrees to Radians
 * @param r The degree value
 * @return float The converted value in radians
 */
float	deg_to_rad(float r)
{
	return (r * DEG_TO_RAD);
}

void	axis_angle(t_mat4 *rot_mat, const t_vector *ax, float angle)
{
	(*rot_mat)[0][0] = cos(angle) + ax->x * ax->x * (1 - cos(angle));
	(*rot_mat)[0][1] = ax->x * ax->y * (1 - cos(angle)) - ax->z * sin(angle);
	(*rot_mat)[0][2] = ax->x * ax->z * (1 - cos(angle)) + ax->y * sin(angle);
	(*rot_mat)[0][3] = 0;
	(*rot_mat)[1][0] = ax->x * ax->y * (1 - cos(angle)) + ax->z * sin(angle);
	(*rot_mat)[1][1] = cos(angle) + ax->y * ax->y * (1 - cos(angle));
	(*rot_mat)[1][2] = ax->y * ax->z * (1 - cos(angle)) - ax->x * sin(angle);
	(*rot_mat)[1][3] = 0;
	(*rot_mat)[2][0] = ax->z * ax->x * (1 - cos(angle)) - ax->y * sin(angle);
	(*rot_mat)[2][1] = ax->z * ax->y * (1 - cos(angle)) + ax->x * sin(angle);
	(*rot_mat)[2][2] = cos(angle) + ax->z * ax->z * (1 - cos(angle));
	(*rot_mat)[2][3] = 0;
	(*rot_mat)[3][0] = 0;
	(*rot_mat)[3][1] = 0;
	(*rot_mat)[3][2] = 0;
	(*rot_mat)[3][3] = 1;
}

// void	calculate_camera_transform(t_scene *scene)
// {
// 	t_vector		from;
// 	t_vector		up;

// 	from.x = scene->camera.position.x;
// 	from.y = scene->camera.position.y;
// 	from.z = scene->camera.position.z;
// 	from.w = 1;
// 	normalize_vec(&scene->camera.dir);
// 	up.x = 0;
// 	up.y = 1;
// 	up.z = 0;
// 	up.w = 0;
// 	view_transform(&scene->camera.transform, &from, &up,
// 		&scene->camera.dir);
// 	mat_inverse(&scene->camera.inv_trans, &scene->camera.transform);
// }

// void	multiply_transforms(t_shape *shape, t_mat4 *scale, t_mat4 *rot,
// 	t_mat4 *translate)
// {
// 	// t_mat4	temp;

// 	// mat_multiply(&shape->transf, translate, &shape->added_rots);
// 	// ft_memcpy(&temp, &shape->transf, sizeof(t_mat4));	
// 	// mat_multiply(&shape->transf, &temp, rot);
// 	// ft_memcpy(translate, &shape->transf, sizeof(t_mat4));
// 	// mat_multiply(&shape->transf, translate, scale);
// 	// mat_inverse(&shape->inv_transf, &shape->transf);
// 	// ft_memcpy(&shape->norm_transf, &shape->inv_transf, sizeof(t_mat4));
// 	// transpose_matrix(&shape->norm_transf);
// }

