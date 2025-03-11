/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:17 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/11 18:50:56 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "MLX42.h"

int	main(int ac, char **av)
{
	int				fd;
	t_scene_data	data;

	if (ac != 2)
		handle_error(ERR_ARGS, NULL);
	fd = open(av[1], O_RDONLY);
	parse_elements(&data, fd);
	close(fd);
	render_scene(&data);
	return (0);
}

render_scene(t_scene_data *data)
{
	t_window_data	window_data;

	window_data.mlx_window = mlx_init(1080, 720, "miniRT", false);
	if (!window_data.mlx_window)
		error_handler(ERR_WINDOW, &window_data);
	window_data.mlx_image = mlx_new_image(window_data.mlx_window, 1080, 720);
	if (!window_data.mlx_image)
		error_handler(ERR_IMAGE, &window_data);
	window_data.image_data = (unsigned char *)window_data.mlx_image->pixels;
	if (!window_data.image_data)
		error_handler(ERR_DATA, &window_data);
	mlx_image_to_window(window_data.mlx_window, window_data.mlx_image, 0, 0);
	mlx_loop(window_data.mlx_window);
	// do stuff
	clean_exit(EXIT_SUCCESS, &window_data);
}
