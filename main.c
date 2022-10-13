/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:58:45 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 17:56:10 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Check arguments for invalid input
void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("WRONG NUMBER OF ARGUMENTS!!!!!!!!!!!!!!!!!!!!!!\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strnstr(argv[1], ".ppm", ft_strlen(argv[1])) == NULL
		&& ft_strnstr(argv[1], ".PPM", ft_strlen(argv[1])) == NULL
		&& ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == NULL)
	{
		ft_printf("Only ppm and fdf files are supported\n");
		exit(EXIT_FAILURE);
	}
}

// Used by create_vars() to set default values for the vars struct
void	fill_vars(t_vars *vars, void *mlx, t_map *map)
{
	vars->mlx = mlx;
	vars->map = map;
	vars->img = vars->data->img;
	vars->scale = 1;
	vars->translate_x = vars->win_x / 4;
	vars->translate_y = vars->win_y / 4;
	if (map->min_x < 0)
		vars->translate_x -= map->min_x;
	if (map->min_y < 0)
		vars->translate_y -= map->min_y;
	vars->m_prev_x = -1;
	vars->m_prev_y = -1;
	vars->m_x = -1;
	vars->m_y = -1;
	vars->proj = 'i';
	vars->theme = 0xFFFFFF;
}

// Create a vars struct
t_vars	*create_vars(void *mlx, t_map *map)
{
	t_vars	*vars;

	vars = ft_calloc(1, sizeof(t_vars));
	if (vars == NULL)
		return (NULL);
	vars->win_x = abs(map->max_x - map->min_x) * 2 + 51;
	vars->win_y = abs(map->max_y - map->min_y) * 2 + 51;
	vars->win = mlx_new_window(mlx, vars->win_x, vars->win_y, "fdf");
	vars->data = ft_calloc(1, sizeof(t_data));
	if (vars->data == NULL)
	{
		free(vars->data);
		return (NULL);
	}
	vars->data->img = mlx_new_image(mlx, vars->win_x, vars->win_y);
	vars->data->addr = mlx_get_data_addr(vars->data->img,
			&vars->data->bits_per_pixel, &vars->data->line_length,
			&vars->data->endian);
	fill_vars(vars, mlx, map);
	return (vars);
}

// FDF
int	main(int argc, char **argv)
{
	void	*mlx;
	t_map	*map;
	t_vars	*vars;

	check_args(argc, argv);
	mlx = mlx_init();
	if (ft_strnstr(argv[1], ".ppm", ft_strlen(argv[1])) != NULL
		|| ft_strnstr(argv[1], ".PPM", ft_strlen(argv[1])) != NULL)
		map = read_map_from_ppm(argv[1]);
	else
		map = read_map(argv[1]);
	vars = create_vars(mlx, map);
	mlx_hook(vars->win, 2, (1L << 0), handle_keypress, vars);
	mlx_hook(vars->win, 5, 0, handle_mouse_up, vars);
	mlx_mouse_hook(vars->win, handle_mouse_down, vars);
	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_loop_hook(mlx, mouse_rotate, vars);
	draw_frame(vars);
	mlx_loop(mlx);
	free(vars->data);
	free_map(map);
	mlx_destroy_image(vars->mlx, vars->img);
	free(mlx);
	free(vars);
}
