/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:54:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 18:23:30 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Switch between different color themes
void	handle_color_change(int key, t_vars *vars)
{
	if (key == KEY_C || key == L_KEY_C)
	{
		if (vars->theme == 0xFFA32B)
			vars->theme = 0xFF44CC;
		else if (vars->theme == 0xFF44CC)
			vars->theme = 0x39FF14;
		else if (vars->theme == 0x39FF14)
			vars->theme = 0XFFFFFF;
		else if (vars->theme == 0XFFFFFF)
			vars->theme = 0xFFA32B;
		draw_frame(vars);
	}
}

// Handle transformation keys
void	check_transformation_keys(int key, t_vars *vars)
{
	if ((key == KEY_LEFT || key == L_KEY_LEFT))
		rotate_y(vars->map, 5);
	if ((key == KEY_RIGHT || key == L_KEY_RIGHT))
		rotate_y(vars->map, -5);
	if ((key == KEY_UP || key == L_KEY_UP))
		rotate_x(vars->map, 5);
	if ((key == KEY_DOWN || key == L_KEY_DOWN))
		rotate_x(vars->map, -5);
	if (key == KEY_Q || key == L_KEY_Q)
		rotate_z(vars->map, 5);
	if (key == KEY_E || key == L_KEY_E)
		rotate_z(vars->map, -5);
	if (key == KEY_W || key == L_KEY_W)
		vars->translate_y -= 10;
	if (key == KEY_A || key == L_KEY_A)
		vars->translate_x -= 10;
	if (key == KEY_S || key == L_KEY_S)
		vars->translate_y += 10;
	if (key == KEY_D || key == L_KEY_D)
		vars->translate_x += 10;
	if (key == KEY_PLUS || key == L_KEY_PLUS)
		vars->scale += 0.1;
	if ((key == KEY_MINUS || key == L_KEY_MINUS) && vars->scale > 0)
		vars->scale -= 0.1;
	handle_color_change(key, vars);
}

// Handle projection change key
void	check_projection_keys(int key, t_vars *vars)
{
	if (key == KEY_P || key == L_KEY_P)
	{
		if (vars->proj == 'i')
		{
			vars->proj = 'c';
		}
		else if (vars->proj == 'c')
		{
			vars->proj = 'i';
		}
	}
}

// Handle keyboard input
int	handle_keypress(int key, t_vars *vars)
{
	if (key == KEY_ESC || key == L_KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		return (0);
	}
	check_projection_keys(key, vars);
	check_transformation_keys(key, vars);
	if (key == KEY_LEFT || key == L_KEY_LEFT || key == KEY_RIGHT
		|| key == L_KEY_RIGHT || key == KEY_UP || key == L_KEY_UP
		|| key == KEY_DOWN || key == L_KEY_DOWN || key == KEY_Q
		|| key == L_KEY_Q || key == KEY_E || key == L_KEY_E || key == KEY_W
		|| key == L_KEY_W || key == KEY_A || key == L_KEY_A || key == KEY_S
		|| key == L_KEY_S || key == KEY_D || key == L_KEY_D || key == KEY_PLUS
		|| key == L_KEY_PLUS || key == KEY_MINUS || key == L_KEY_MINUS
		|| key == KEY_P || key == L_KEY_P || key == KEY_C)
	{
		rotate_points(vars->map);
		project_points(vars->map, vars->scale, vars->proj);
		draw_frame(vars);
	}
	return (0);
}
