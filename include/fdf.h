/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:56:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 16:59:50 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdbool.h>
# include <fcntl.h>
# include "libft.h"
# define PI 3.14159265359
# define RAD_TO_DEG 57.2957795131
# define DEG_TO_RAD 0.01745329251
# define MAX_POINT_COUNT 3000

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif

typedef struct s_vector	t_vector;
struct s_vector
{
	float	x;
	float	y;
	float	z;
	float	w;
};

typedef struct s_point	t_point;
struct s_point
{
	int16_t	height;
	uint8_t	color_idx;
};

typedef float			t_mat4[4][4];

typedef struct s_fdf	t_fdf;
struct s_fdf
{
	t_point	*points;
	int		colors[256];
	int32_t	point_count;
	int32_t	max_size;
	int32_t	max_x;
	int32_t	max_y;
	int16_t	max_z;
	int16_t	min_z;
	uint8_t	num_colors;
	t_mat4	transform_mat;
	float	scale;
};

void	mat_multiply(t_mat4 *res, const t_mat4 *m1, const t_mat4 *m2);
void	mat_vec_multiply(t_vector *res, const t_mat4 *mat,
			const t_vector *vec);
void	identity_matrix(t_mat4 *mat);
void	translate_matrix(t_mat4 *mat, float x, float y, float z);
void	scaling_matrix(t_mat4 *mat, float x, float y, float z);
void	rotation_matrix_x(t_mat4 *mat, float r);
void	rotation_matrix_y(t_mat4 *mat, float r);
void	rotation_matrix_z(t_mat4 *mat, float r);
void	add_vec(t_vector *res, const t_vector *v1, const t_vector *v2);
void	sub_vec(t_vector *res, const t_vector *v1, const t_vector *v2);
void	scale_vec(t_vector *res, const t_vector *v, float scale);
void	negate_vec(t_vector *res, const t_vector *v);
float	vec_magnitude(const t_vector *vec);
void	normalize_vec(t_vector *vec);
float	dot_product(const t_vector *v1, const t_vector *v2);

uint8_t	add_color(t_fdf *fdf, char *buffer, int fd, int *idx);
int		read_color(char *buffer, int fd, int *idx);

void	parse_map(t_fdf *fdf, int fd);
void	resize_points(t_fdf *fdf, size_t new_size);
void	skip_whitespace(t_fdf *fdf, char *buffer, int fd, int *idx);


void	calculate_transforms(t_fdf *fdf);

#endif