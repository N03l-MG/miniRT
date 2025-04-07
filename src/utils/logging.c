/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:04:11 by nmonzon           #+#    #+#             */
/*   Updated: 2025/03/21 16:04:27 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	printlog(t_log_type log_type, char *message)
{
	if (log_type == LOG)
		ft_fprintf(1, MAGENTA "Log: %s\n" RESET, message);
	else if (log_type == WARNING)
		ft_fprintf(1, YELLOW "Warning:\n%s\n" RESET, message);
}

void	scene_debug(t_scene_data *scene)
{
	printf(BLUE "=== Scene Info ===\n");
	printf("Window dimensions: %d x %d\n", WIDTH, HEIGHT);
	printf("Default Shadow Samples: %d\n", scene->samples);
	printf("\n~~ Camera ~~\n");
	printf("Position: %.2f, %.2f, %.2f\n", scene->cam->pos_x, scene->cam->pos_y, scene->cam->pos_z);
	printf("Direction Vector: %.2f, %.2f, %.2f\n", scene->cam->vec_x, scene->cam->vec_y, scene->cam->vec_z);
	printf("Field of View: %.2f\n", scene->cam->fov);
	printf("\n~~ Ambient Light ~~\n");
	printf("Intensity: %.2f\n", scene->ambient->ratio);
	printf("Color: %d, %d, %d\n", scene->ambient->col.r, scene->ambient->col.g, scene->ambient->col.b);
	printf("\n~~ Point Light ~~\n");
	t_light *light = get_scene_light(scene);
	if (light)
	{
		printf("Position: %.2f, %.2f, %.2f\n", light->pos_x, light->pos_y, light->pos_z);
		printf("Intensity: %.2f\n", light->brightness);
		printf("Color: %d, %d, %d\n", light->col.r, light->col.g, light->col.b);
	}
	else
		printf("No light found, scene using default dark-light.\n");
	printf("\n~~ Assets ~~\n");
	printf("Number of assets: %ld\n", scene->assets ? scene->assets->size - 1 : 0);
	if (scene->assets)
	{
		for (size_t i = 0; i < scene->assets->size; i++)
		{
			t_asset_node *node = scene->assets->head;
			for (size_t j = 0; j < i; j++)
				node = node->next;
			if (node->type == AST_SPHERE)
			{
				printf("Sphere\n");
				printf("Position: %.2f, %.2f, %.2f\n", ((t_sphere *)node->asset_struct)->pos_x,
					((t_sphere *)node->asset_struct)->pos_y, ((t_sphere *)node->asset_struct)->pos_z);
				printf("Diameter: %.2f\n", ((t_sphere *)node->asset_struct)->diameter);
				printf("Color: %d, %d, %d\n", ((t_sphere *)node->asset_struct)->col.r,
					((t_sphere *)node->asset_struct)->col.g, ((t_sphere *)node->asset_struct)->col.b);
				printf("Roughness: %.2f\n", ((t_sphere *)node->asset_struct)->roughness);
				printf("Reflectivity: %.2f\n", ((t_sphere *)node->asset_struct)->reflect);
			}
			else if (node->type == AST_PLANE)
			{
				printf("Plane\n");
				printf("Position: %.2f, %.2f, %.2f\n", ((t_plane *)node->asset_struct)->pos_x,
					((t_plane *)node->asset_struct)->pos_y, ((t_plane *)node->asset_struct)->pos_z);
				printf("Direction Vector: %.2f, %.2f, %.2f\n", ((t_plane *)node->asset_struct)->vec_x,
					((t_plane *)node->asset_struct)->vec_y, ((t_plane *)node->asset_struct)->vec_z);
				printf("Color: %d, %d, %d\n", ((t_plane *)node->asset_struct)->col.r,
					((t_plane *)node->asset_struct)->col.g, ((t_plane *)node->asset_struct)->col.b);
				printf("Roughness: %.2f\n", ((t_plane *)node->asset_struct)->roughness);
				printf("Reflectivity: %.2f\n", ((t_plane *)node->asset_struct)->reflect);
			}
			else if (node->type == AST_CYLINDER)
			{
				printf("Cylinder\n");
				printf("Position: %.2f, %.2f, %.2f\n", ((t_cylinder *)node->asset_struct)->pos_x,
					((t_cylinder *)node->asset_struct)->pos_y, ((t_cylinder *)node->asset_struct)->pos_z);
				printf("Direction Vector: %.2f, %.2f, %.2f\n", ((t_cylinder *)node->asset_struct)->vec_x,
					((t_cylinder *)node->asset_struct)->vec_y, ((t_cylinder *)node->asset_struct)->vec_z);
				printf("Diameter: %.2f\n", ((t_cylinder *)node->asset_struct)->diameter);
				printf("Height: %.2f\n", ((t_cylinder *)node->asset_struct)->height);
				printf("Color: %d, %d, %d\n", ((t_cylinder *)node->asset_struct)->col.r,
					((t_cylinder *)node->asset_struct)->col.g, ((t_cylinder *)node->asset_struct)->col.b);
				printf("Roughness: %.2f\n", ((t_cylinder *)node->asset_struct)->roughness);
				printf("Reflectivity: %.2f\n", ((t_cylinder *)node->asset_struct)->reflect);
			}
			else if (node->type == AST_OBJ)
			{
				printf("Obj Asset\n");
				printf("Position: %.2f, %.2f, %.2f\n", ((t_obj *)node->asset_struct)->pos_x,
					((t_obj *)node->asset_struct)->pos_y, ((t_obj *)node->asset_struct)->pos_z);
				printf("Direction Vector: %.2f, %.2f, %.2f\n", ((t_obj *)node->asset_struct)->vec_x,
					((t_obj *)node->asset_struct)->vec_y, ((t_obj *)node->asset_struct)->vec_z);
				printf("Scale: %.2f\n", ((t_obj *)node->asset_struct)->scale);
				printf("Color: %d, %d, %d\n", ((t_obj *)node->asset_struct)->col.r,
					((t_obj *)node->asset_struct)->col.g, ((t_obj *)node->asset_struct)->col.b);
				printf("Roughness: %.2f\n", ((t_obj *)node->asset_struct)->roughness);
				printf("Reflectivity: %.2f\n", ((t_obj *)node->asset_struct)->reflect);
				printf("Vertices: %d\n", ((t_obj *)node->asset_struct)->num_vertices);
				for (int k = 0; k < ((t_obj *)node->asset_struct)->num_vertices; k++)
					printf("Vertex %d: %.2f, %.2f, %.2f\n", k, ((t_obj *)node->asset_struct)->vertices[k].x,
						((t_obj *)node->asset_struct)->vertices[k].y, ((t_obj *)node->asset_struct)->vertices[k].z);
				printf("Normals: %d\n", ((t_obj *)node->asset_struct)->num_normals);
				printf("UVs: %d\n", ((t_obj *)node->asset_struct)->num_uvs);
				printf("Faces: %d\n", ((t_obj *)node->asset_struct)->num_faces);
				for (int k = 0; k < ((t_obj *)node->asset_struct)->num_faces; k++)
				{
					printf("Face %d: ", k);
					for (int l = 0; l < 3; l++)
						printf("%d/%d/%d ", ((t_obj *)node->asset_struct)->faces[k].v[l],
							((t_obj *)node->asset_struct)->faces[k].vt[l], ((t_obj *)node->asset_struct)->faces[k].vn[l]);
					printf("\n");
				}
			}
			printf("\n");
		}
		printf("=================\n" RESET);
	}
}
