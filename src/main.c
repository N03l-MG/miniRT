/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:17 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/14 16:25:44 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void    print_scene_data(t_scene_data *data) // Temp debug function
// {
// 	t_asset_node *current;

// 	// Print ambient light
// 	if (data->ambient)
// 	{
// 		printf("Ambient Light:\n");
// 		printf("  Ratio: %.2f\n", data->ambient->ratio);
// 		printf("  Color: (%d, %d, %d)\n", data->ambient->r, data->ambient->g, data->ambient->b);
// 	}

// 	// Print camera
// 	if (data->cam)
// 	{
// 		printf("Camera:\n");
// 		printf("  Position: (%.1f, %.1f, %.1f)\n", data->cam->x, data->cam->y, data->cam->z);
// 		printf("  Vector: (%.1f, %.1f, %.1f)\n", data->cam->vx, data->cam->vy, data->cam->vz);
// 		printf("  FOV: %.2f\n", data->cam->fov);
// 	}

// 	// Print assets
// 	current = data->assets->head;
// 	while (current)
// 	{
// 		if (current->type == ASS_LIGHT)
// 		{
// 			t_light *light = (t_light *)current->asset_struct;
// 			printf("Light:\n");
// 			printf("  Position: (%.1f, %.1f, %.1f)\n", light->x, light->y, light->z);
// 			printf("  Brightness: %.2f\n", light->brightness);
// 			printf("  Color: (%d, %d, %d)\n", light->r, light->g, light->b);
// 		}
// 		else if (current->type == ASS_SPHERE)
// 		{
// 			t_sphere *sphere = (t_sphere *)current->asset_struct;
// 			printf("Sphere:\n");
// 			printf("  Position: (%.1f, %.1f, %.1f)\n", sphere->x, sphere->y, sphere->z);
// 			printf("  Diameter: %.2f\n", sphere->d);
// 			printf("  Color: (%d, %d, %d)\n", sphere->r, sphere->g, sphere->b);
// 		}
// 		else if (current->type == ASS_PLANE)
// 		{
// 			t_plane *plane = (t_plane *)current->asset_struct;
// 			printf("Plane:\n");
// 			printf("  Position: (%.1f, %.1f, %.1f)\n", plane->x, plane->y, plane->z);
// 			printf("  Vector: (%.2f, %.2f, %.2f)\n", plane->vx, plane->vy, plane->vz);
// 			printf("  Color: (%d, %d, %d)\n", plane->r, plane->g, plane->b);
// 		}
// 		else if (current->type == ASS_CYLINDER)
// 		{
// 			t_cylinder *cylinder = (t_cylinder *)current->asset_struct;
// 			printf("Cylinder:\n");
// 			printf("  Position: (%.1f, %.1f, %.1f)\n", cylinder->x, cylinder->y, cylinder->z);
// 			printf("  Vector: (%.2f, %.2f, %.2f)\n", cylinder->vx, cylinder->vy, cylinder->vz);
// 			printf("  Diameter: %.2f\n", cylinder->d);
// 			printf("  Height: %.2f\n", cylinder->h);
// 			printf("  Color: (%d, %d, %d)\n", cylinder->r, cylinder->g, cylinder->b);
// 		}
// 		current = current->next;
// 	}
// }

int	main(int ac, char **av)
{
	int				fd;
	t_scene_data	data;

	if (ac != 2)
		fatal_error(ERR_ARGS, NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		fatal_error(ERR_FILE, NULL);
	parse_elements(&data, fd);
	close(fd);
	//print_scene_data(&data);
	render_scene(&data);
	return (0);
}
