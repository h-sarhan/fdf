/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:35:32 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 19:23:41 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "printf/ft_printf.h"

# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# define ON_DESTROY 17
# define PI           3.14159265358979323846F
# define KEY_ESC 53
# define L_KEY_ESC 65307
# define KEY_W 13
# define L_KEY_W 119
# define KEY_A 0
# define L_KEY_A 97
# define KEY_S 1
# define L_KEY_S 115
# define KEY_D 2
# define L_KEY_D 100
# define KEY_LEFT 123
# define L_KEY_LEFT 65361
# define KEY_RIGHT 124
# define L_KEY_RIGHT 65363
# define KEY_UP 126
# define L_KEY_UP 65362
# define KEY_DOWN 125
# define L_KEY_DOWN 65364
# define KEY_Q 12
# define L_KEY_Q 113
# define KEY_E 14
# define L_KEY_E 101
# define KEY_PLUS 24
# define L_KEY_PLUS 61
# define KEY_MINUS 27
# define L_KEY_MINUS 45
# define KEY_P 35
# define L_KEY_P 112
# define KEY_C 8
# define L_KEY_C 99

struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
};

typedef struct s_point		t_point;

struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};
typedef struct s_data		t_data;

struct s_quaternion {
	float	x;
	float	y;
	float	z;
	float	w;
};

typedef struct s_quaternion	t_quaternion;

struct s_map
{
	int				num_rows;
	int				num_cols;
	t_point			***points;
	t_point			***points_copy;
	t_point			***proj_pts;
	int				rot_x;
	int				rot_y;
	t_point			*look;
	int				rot_z;
	int				min_x;
	int				max_x;
	int				min_y;
	int				max_y;
	float			max_og_x;
	float			max_og_y;
	float			max_og_z;
	t_quaternion	*orientation;
};
typedef struct s_map		t_map;

struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	*map;
	void	*img;
	t_data	*data;
	float	scale;
	int		win_x;
	int		win_y;
	int		translate_x;
	int		translate_y;
	int		drawing_frame;
	int		m_prev_x;
	int		m_prev_y;
	int		m_x;
	int		m_y;
	int		m_key;
	int		pan_x;
	int		pan_y;
	char	proj;
	int		theme;
};

typedef struct s_vars		t_vars;

void			my_mlx_pixel_put(int x, int y, int color, t_vars *vars);
unsigned int	hextoi(char *str);
void			draw_line(t_point *p1, t_point *p2, t_vars *vars);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				add_color(int color1, int color2);
int				color_mix(int c1, int c2, float mix);
void			draw_frame(t_vars *vars);
void			find_min_max(t_map *map, t_point ***points);
void			exit_msg(char *msg, int code);
void			free_split_array(char **arr);
t_map			*create_map(void);
t_point			*create_point(float x, float y, float z, int color);
t_map			*read_map_from_ppm(char *map_path);
void			rotate_x(t_map *map, float rot);
void			rotate_y(t_map *map, float rot);
void			rotate_z(t_map *map, float rot);
void			rotate_points(t_map *map);
void			project_point(t_point *projected, t_point *orig, char proj);
void			project_points(t_map *map, float scale, char proj);
void			free_map(t_map *map);
int				handle_mouse_down(int key_code, int x, int y, void *params);
int				handle_mouse_up(int key_code, int x, int y, void *params);
int				mouse_rotate(void *params);
int				close_window(void *params);
int				handle_keypress(int key_code, t_vars *vars);
t_map			*read_map(char *map_path);
void			*create_new_image(t_vars *vars);
t_quaternion	*create_quaternion(float x, float y, float z, float w);
t_quaternion	*rotate_quaternion(t_quaternion *rot, t_quaternion *q);
t_quaternion	*create_quaternion_rotation(float rot, t_point *axis);
void			rotate_point(t_quaternion *q, t_point *p);

#endif