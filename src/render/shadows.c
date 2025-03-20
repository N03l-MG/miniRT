#include "miniRT.h"

static t_vector	rand_spread(float radius)
{
	t_vector	p;
	do {
		p = vec_new(
			//TODO: make own rand function
			(rand() / (float)RAND_MAX) * 2.0f - 1.0f,
			(rand() / (float)RAND_MAX) * 2.0f - 1.0f,
			(rand() / (float)RAND_MAX) * 2.0f - 1.0f
		);
	} while (vec_length(p) > 1.0f);
	return vec_scale(p, radius);
}

float	shadow_caster(t_scene_data *data, t_vector intersect, t_vector normal, t_light *light)
{
	t_vector light_pos = vec_new(light->pos_x, light->pos_y, light->pos_z);
	t_vector light_dir = vec_normalize(vec_sub(light_pos, intersect));
	t_ray shadow_ray;
	float light_distance = vec_length(vec_sub(light_pos, intersect));
	shadow_ray.origin = vec_add(intersect, vec_scale(normal, 0.001f));
	shadow_ray.direction = light_dir;
	if (vec_dot(normal, light_dir) < 0)
        return 0.0f;
	float shadow_intensity = 0.0f;
	for (int i = 0; i < data->samples; i++)
	{
		t_vector jitter_pos = vec_add(light_pos, rand_spread(1.5f));
		t_vector jitter_dir = vec_normalize(vec_sub(jitter_pos, intersect));
		shadow_ray.direction = jitter_dir;
		if (is_occluded(data, shadow_ray, light_distance))
			shadow_intensity += 1.0f - (fmax(fmin(light_distance, 500.0f), 0.0f) / 500);
	}
	return (1.0f - (shadow_intensity / data->samples));
}

float	ambient_occlusion(t_scene_data *data, t_vector point, t_vector normal)
{
	float occlusion = 0.0f;
	float max_distance = 2.0f;

	for (int i = 0; i < data->samples; i++)
	{
		t_vector random_dir = rand_spread(1.0f);
		if (vec_dot(random_dir, normal) < 0)
			random_dir = vec_scale(random_dir, -1.0f);
		t_ray ao_ray;
		ao_ray.origin = vec_add(point, vec_scale(normal, 0.001f));
		ao_ray.direction = vec_normalize(random_dir);
		t_asset_node *node = data->assets->head;
		while (node)
		{
			double t;
			if (node->type == ASS_PLANE)
			{
				if (plane_intersect((t_plane *)node->asset_struct, ao_ray, &t)
					&& t > 0.001f && t < max_distance)
					occlusion += 1.0f;
			}
			node = node->next;
		}
	}
	return 1.0f - (occlusion / (float)data->samples);
}
