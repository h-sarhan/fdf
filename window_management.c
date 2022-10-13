/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:25:01 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 18:23:18 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_mouse_down(int key_code, int x, int y, void *params)
{
	t_vars	*vars;

	(void)x;
	(void)y;
	vars = params;
	vars->m_key = key_code;
	if (key_code == 4)
		vars->scale += 0.1;
	else if (key_code == 5 && vars->scale > 0)
		vars->scale -= 0.1;
	rotate_points(vars->map);
	project_points(vars->map, vars->scale, vars->proj);
	draw_frame(vars);
	return (0);
}

int	handle_mouse_up(int key_code, int x, int y, void *params)
{
	t_vars	*vars;

	(void)x;
	(void)y;
	(void)key_code;
	vars = params;
	vars->m_key = 0;
	return (0);
}

int	mouse_rotate(void *params)
{
	t_vars	*vars;

	vars = params;
	if (vars->m_key == 3)
	{
		vars->m_prev_x = vars->m_x;
		vars->m_prev_y = vars->m_y;
		mlx_mouse_get_pos(vars->win, &vars->m_x, &vars->m_y);
		if (vars->m_x != vars->m_prev_x || vars->m_y != vars->m_prev_y)
		{
			if (vars->m_prev_x < vars->m_x)
				rotate_y(vars->map, -3);
			else if (vars->m_prev_x > vars->m_x)
				rotate_y(vars->map, 3);
			if (vars->m_prev_y < vars->m_y)
				rotate_x(vars->map, -3);
			else if (vars->m_prev_y > vars->m_y)
				rotate_x(vars->map, 3);
			rotate_points(vars->map);
			project_points(vars->map, vars->scale, vars->proj);
			draw_frame(vars);
		}
	}
	return (0);
}

int	close_window(void *params)
{
	t_vars	*vars;

	vars = params;
	ft_putendl_fd("QUITTING PROGRAM!", 1);
	free_map(vars->map);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img);
	free(vars->data);
	free(vars->mlx);
	free(vars);
	exit(EXIT_SUCCESS);
	return (0);
}

void	*create_new_image(t_vars *vars)
{
	void	*old_image;

	old_image = vars->img;
	vars->data->img = mlx_new_image(vars->mlx, vars->win_x, vars->win_y);
	vars->img = vars->data->img;
	vars->data->addr = mlx_get_data_addr(vars->data->img,
			&vars->data->bits_per_pixel,
			&vars->data->line_length, &vars->data->endian);
	return (old_image);
}
