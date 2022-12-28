/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:56:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 13:24:14 by hsarhan          ###   ########.fr       */
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
# define MAX_POINT_COUNT 1000

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif
typedef enum e_parse_phase	t_parse_phase;
enum	e_parse_phase
{
	HEIGHT,
	COLOR,
	WHITESPACE,
	NEW_LINE,
};

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
	int		color;
	short	height;
};

typedef float	t_mat4[4][4];

typedef struct s_fdf	t_fdf;
struct s_fdf
{
	t_point	*points;
	size_t	point_count;
	size_t	max_size;
	size_t	width;
	size_t	height;
	int		theme;
};


void	mat_multiply(t_mat4 *res, const t_mat4 *m1, const t_mat4 *m2);
void	mat_vec_multiply(t_vector *res, const t_mat4 *mat,
			const t_vector *vec);
void	identity_matrix(t_mat4 *mat);
void	transpose_matrix(t_mat4 *mat);
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

void	parse_map(t_fdf *fdf, int fd);
void	resize_points(t_fdf *fdf);
void	skip_whitespace(char *buffer, int fd, int *idx);

#endif