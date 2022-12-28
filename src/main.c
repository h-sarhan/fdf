/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 00:58:05 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 01:35:34 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	print_points(t_fdf *fdf)
{
	for (size_t i = 0; i < fdf->point_count; i++)
	{
		printf("%d ", fdf->points[i].height);
	}
	printf("\nHeight: %ld\n", fdf->height);
	printf("Width: %ld\n", fdf->width);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	ft_bzero(&fdf, sizeof(t_fdf));
	fdf.max_size = MAX_POINT_COUNT;
	if (argc != 2)
	{
		exit(1);
	}
	int	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("FAILED TO OPEN\n");
	}
	parse_map(&fdf, fd);
	close(fd);
	print_points(&fdf);
	free(fdf.points);
}