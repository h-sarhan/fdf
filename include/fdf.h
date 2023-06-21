/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:56:05 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/21 11:04:47 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "libft.h"
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#define PI              3.14159265359
#define RAD_TO_DEG      57.2957795131
#define DEG_TO_RAD      0.01745329251
#define MAX_POINT_COUNT 3000
#define ROT_SPEED       1
#define MOVE_SPEED      0.05
#define ZOOM_SPEED      0.01
#define EPSILON         0.001
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100000
#endif

#define SCREEN_W 700
#define SCREEN_H 700

#ifdef __linux__
#include "../lib/mlx_linux/mlx.h"
#else
#include "../lib/mlx/mlx.h"
#endif

#ifdef __linux__
#define KEY_ESC         65307
#define KEY_W           119
#define KEY_A           97
#define KEY_S           115
#define KEY_D           100
#define KEY_O           111
#define KEY_LEFT        65361
#define KEY_RIGHT       65363
#define KEY_UP          65362
#define KEY_DOWN        65364
#define KEY_Q           113
#define KEY_E           101
#define KEY_PLUS        61
#define KEY_MINUS       45
#define KEY_P           112
#define KEY_C           99
#define KEY_TAB         65289
#define KEY_SPACE       32
#define KEY_R           114
#define KEY_M           109
#define KEY_1           49
#define KEY_2           50
#define KEY_3           51
#define KEY_4           52
#define KEY_5           53
#define KEY_6           54
#define KEY_7           55
#define KEY_8           56
#define KEY_9           57
#define KEY_RETURN      65293
#define KEY_SHIFT       65505
#define LEFT_MOUSE_DOWN 1
#define KEY_T           17
#define KEY_X           7
#define KEY_Y           16
#define KEY_Z           6
#else
#define KEY_ESC         53
#define KEY_W           13
#define KEY_A           0
#define KEY_S           1
#define KEY_D           2
#define KEY_O           31
#define KEY_LEFT        123
#define KEY_RIGHT       124
#define KEY_UP          126
#define KEY_DOWN        125
#define KEY_Q           12
#define KEY_E           14
#define KEY_PLUS        24
#define KEY_MINUS       27
#define KEY_P           35
#define KEY_C           8
#define KEY_TAB         48
#define KEY_SPACE       49
#define KEY_R           15
#define KEY_M           46
#define KEY_1           18
#define KEY_2           19
#define KEY_3           20
#define KEY_4           21
#define KEY_5           23
#define KEY_6           22
#define KEY_7           26
#define KEY_8           28
#define KEY_9           25
#define KEY_RETURN      36
#define KEY_SHIFT       257
#define LEFT_MOUSE_DOWN 1
#define KEY_T           17
#define KEY_X           7
#define KEY_Y           16
#define KEY_Z           6
#endif

typedef struct s_keys t_keys;
struct s_keys
{
    bool w;
    bool a;
    bool s;
    bool d;
    bool up;
    bool down;
    bool left;
    bool right;
    bool q;
    bool e;
    bool plus;
    bool minus;
    bool tab;
    bool c;
    bool shift;
    bool x;
    bool y;
    bool z;
};

typedef struct s_point t_point;
struct s_point
{
    uint32_t color;
    int16_t height;
};

typedef float t_mat2[2][2];
typedef float t_mat3[3][3];
typedef float t_mat4[4][4];
typedef float t_vec4[4];

typedef struct s_fdf t_fdf;
struct s_fdf
{
    t_mat4 transform_mat;
    t_mat4 cam_transform;
    t_mat4 orientation;
    t_mat4 translation;
    t_mat4 projection;
    t_mat4 inv_projection;
    t_keys keys;
    t_point *points;
    t_vec4 cam_look;
    t_vec4 cam_pos;
    float cam_theta;
    float cam_phi;
    bool cam_mode;
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int32_t point_count;
    int32_t max_size;
    int32_t max_x;
    int32_t max_y;
    int32_t max_z;
    int32_t min_z;
    int bpp;
    int line_size;
    int endian;
    float scale;
};

void mat_multiply(t_mat4 *res, const t_mat4 *m1, const t_mat4 *m2);
void mat_vec_multiply(t_vec4 *res, const t_mat4 *mat, const t_vec4 *vec);
void identity_matrix(t_mat4 *mat);
void translate_matrix(t_mat4 *mat, float x, float y, float z);
void scaling_matrix(t_mat4 *mat, float x, float y, float z);
void rotation_matrix_x(t_mat4 *mat, float r);
void rotation_matrix_y(t_mat4 *mat, float r);
void rotation_matrix_z(t_mat4 *mat, float r);
void add_vec(t_vec4 *res, const t_vec4 *v1, const t_vec4 *v2);
void sub_vec(t_vec4 *res, const t_vec4 *v1, const t_vec4 *v2);
void scale_vec(t_vec4 *res, const t_vec4 *v, float scale);
void negate_vec(t_vec4 *res, const t_vec4 *v);
float vec_magnitude(const t_vec4 *vec);
void normalize_vec(t_vec4 *vec);
float dot_product(const t_vec4 *v1, const t_vec4 *v2);

int read_color(char *buffer, int fd, int *idx);

void parse_map(t_fdf *fdf, int fd);
void resize_points(t_fdf *fdf, size_t new_size);
void skip_whitespace(char *buffer, int fd, int *idx);

void calculate_transforms(t_fdf *fdf);
int key_press(int key, t_fdf *fdf);
int key_release(int key, t_fdf *fdf);
int render_loop(t_fdf *fdf);
void draw_points(t_fdf *fdf);
void draw_line(t_fdf *fdf, float x0, float y0, float x1, float y1, int c1,
               int c2);
bool clip_line(float *x0, float *y0, float *x1, float *y1);
void viewport_projection(t_mat4 *mat);
void orthographic_projection(t_mat4 *res);
void submat4(t_mat3 *res, const t_mat4 *mat, int row, int col);
double det3(const t_mat3 *mat3);
void mat_inverse(t_mat4 *res, const t_mat4 *mat);
void cross_product(t_vec4 *res, const t_vec4 *v1, const t_vec4 *v2);
void camera_projection(t_mat4 *res, t_vec4 *origin, t_vec4 *up, t_vec4 *look);
void sphere_to_xyz(t_vec4 *vec, double phi, double theta, double r);

#endif