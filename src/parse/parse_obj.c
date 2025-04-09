#include "miniRT.h"

static bool	check_valid(t_obj *obj)
{
	if ((obj->vec_x < -1 || obj->vec_x > 1)
		|| (obj->vec_y < -1 || obj->vec_y > 1)
		|| (obj->vec_z < -1 || obj->vec_z > 1)
		|| (obj->scale < 0)
		|| (obj->roughness < 0 || obj->roughness > 1)
		|| (obj->reflect < 0 || obj->reflect > 1)
		|| (obj->col.r < 0 || obj->col.r > 255)
		|| (obj->col.g < 0 || obj->col.g > 255)
		|| (obj->col.b < 0 || obj->col.b > 255))
		return (printlog(WARNING, "Invalid .obj asset parameters"), false);
	return (true);
}

static char	*read_line(int fd)
{
	char	buffer[1024];
	int		i;
	int		bytes;
	char	c;

	i = 0;
	while ((bytes = read(fd, &c, 1)) > 0 && c != '\n' && i < 1023)
		buffer[i++] = c;
	buffer[i] = '\0';
	//printf("Read line: %s\n", buffer);
	if (bytes <= 0 && i == 0)
		return (NULL);
	return (ft_strdup(buffer));
}

static void	count_alloc_elements(t_obj *obj, int fd)
{
	char	*line;

	obj->num_vertices = 0;
	obj->num_normals = 0;
	obj->num_uvs = 0;
	obj->num_faces = 0;
	
	while ((line = read_line(fd)))
	{
		if (ft_strncmp(line, "v ", 2) == 0)
			obj->num_vertices++;
		else if (ft_strncmp(line, "vn ", 3) == 0)
			obj->num_normals++;
		else if (ft_strncmp(line, "vt ", 3) == 0)
			obj->num_uvs++;
		else if (ft_strncmp(line, "f ", 2) == 0)
			obj->num_faces++;
		gc_free(line);
	}
	obj->vertices = gc_malloc(sizeof(t_vector) * obj->num_vertices);
	obj->normals = gc_malloc(sizeof(t_vector) * obj->num_normals);
	obj->uvs = gc_malloc(sizeof(t_uv) * obj->num_uvs);
	obj->faces = gc_malloc(sizeof(t_face) * obj->num_faces);
	if (!obj->vertices || !obj->normals || !obj->uvs || !obj->faces)
		fatal_error(ERR_MEMORY, NULL);
}

static void	parse_vertex(char *line, t_obj *obj, int index)
{
	t_vector	vertex;
	char		**split;

	split = ft_split(line, ' ');
	vertex.x = ft_atof(split[1]);
	vertex.y = ft_atof(split[2]);
	vertex.z = ft_atof(split[3]);
	obj->vertices[index] = vertex; // Use the local index
	free_split(split);
}

static void	parse_normal(char *line, t_obj *obj, int index)
{
	t_vector	normal;
	char		**split;

	split = ft_split(line, ' ');
	normal.x = ft_atof(split[1]);
	normal.y = ft_atof(split[2]);
	normal.z = ft_atof(split[3]);
	obj->normals[index] = normal; // Use the local index
	free_split(split);
}

static void	parse_uv(char *line, t_obj *obj, int index)
{
	t_uv	uv;
	char	**split;

	split = ft_split(line, ' ');
	uv.u = ft_atof(split[1]);
	uv.v = ft_atof(split[2]);
	obj->uvs[index] = uv; // Use the local index
	free_split(split);
}

static void parse_face(char *line, t_obj *obj, int index)
{
    t_face face;
    char **split;

    split = ft_split(line, ' ');
    for (int i = 0; i < 3; i++) // Ensure only triangles are processed
    {
        char **face_data = ft_split(split[i + 1], '/');
        int num_elements = get_number_of_split_elements(face_data);

        if (num_elements >= 1) // At least vertex index is present
            face.v[i] = ft_atoi(face_data[0]) - 1;
        else
            face.v[i] = -1;
        if (num_elements >= 2 && ft_strlen(face_data[1]) > 0) // Texture index
            face.vt[i] = ft_atoi(face_data[1]) - 1;
        else
            face.vt[i] = -1;
        if (num_elements == 3 && ft_strlen(face_data[2]) > 0) // Normal index
            face.vn[i] = ft_atoi(face_data[2]) - 1;
        else
            face.vn[i] = -1;

        // Validate vertex index
        if (face.v[i] < 0 || face.v[i] >= obj->num_vertices)
        {
            printlog(WARNING, "Invalid vertex index in .obj file");
            free_split(face_data);
            free_split(split);
            return;
        }
        free_split(face_data);
    }
    obj->faces[index] = face;
    free_split(split);
}

static void	parse_obj_data(t_obj *obj, char *filename)
{
	int		fd;
	char	*line;
	int		vertex_index = 0;
	int		normal_index = 0;
	int		uv_index = 0;
	int		face_index = 0;

	obj->vertices = NULL;
	obj->normals = NULL;
	obj->uvs = NULL;
	obj->faces = NULL;
	obj->num_vertices = 0;
	obj->num_normals = 0;
	obj->num_uvs = 0;
	obj->num_faces = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		fatal_error(ERR_OBJFILE, NULL);
	count_alloc_elements(obj, fd);
	close(fd);

	// Reopen the file for the second pass
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		fatal_error(ERR_OBJFILE, NULL);

	while ((line = read_line(fd)))
	{
		if (line == NULL)
			continue;
		if (ft_strncmp(line, "v ", 2) == 0)
		{
			parse_vertex(line, obj, vertex_index);
			vertex_index++;
		}
		else if (ft_strncmp(line, "vn ", 3) == 0)
		{
			parse_normal(line, obj, normal_index);
			normal_index++;
		}
		else if (ft_strncmp(line, "vt ", 3) == 0)
		{
			parse_uv(line, obj, uv_index);
			uv_index++;
		}
		else if (ft_strncmp(line, "f ", 2) == 0)
		{
			parse_face(line, obj, face_index);
			face_index++;
		}
		gc_free(line);
	}
	close(fd);
}

static void	set_params(t_obj *obj, char **param)
{
	obj->roughness = DEFAULT_ROUGHNESS;
	obj->reflect = DEFAULT_REFLECT;
	parse_obj_data(obj, param[1]);
	obj->pos_x = ft_atof(get_split_param(param[2], 0));
	obj->pos_y = ft_atof(get_split_param(param[2], 1));
	obj->pos_z = ft_atof(get_split_param(param[2], 2));
	obj->vec_x = ft_atof(get_split_param(param[3], 0));
	obj->vec_y = ft_atof(get_split_param(param[3], 1));
	obj->vec_z = ft_atof(get_split_param(param[3], 2));
	obj->scale = ft_atof(param[4]);
	obj->col.r = ft_atoi(get_split_param(param[5], 0));
	obj->col.g = ft_atoi(get_split_param(param[5], 1));
	obj->col.b = ft_atoi(get_split_param(param[5], 2));
	if (get_number_of_split_elements(param) >= 7)
		obj->roughness = ft_atof(param[6]);
	if (get_number_of_split_elements(param) >= 8)
		obj->reflect = ft_atof(param[7]);
}

static void	add_obj(t_assets *assets, t_obj *new_obj)
{
	t_asset_node	*new_node;
	t_asset_node	*current;

	if (!check_valid(new_obj))
		return ;
	new_node = gc_malloc(sizeof(t_asset_node));
	if (!new_node)
		fatal_error(ERR_MEMORY, NULL);
	new_node->asset_struct = new_obj;
	new_node->type = AST_OBJ;
	new_node->next = NULL;
	if (assets->head == NULL)
		assets->head = new_node;
	else
	{
		current = assets->head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	assets->size++;
	assets->obj_cnt++;
	printlog(LOG, "Obj setup successful.");
}

int	parse_obj(t_scene_data *data, char **param)
{
	t_obj	*new_obj;

	if (get_number_of_split_elements(param) < 6
		|| get_number_of_split_elements(param) > 8)
		return (printlog(WARNING, "Invalid .obj configuration"), 0);
	if (access(param[1], F_OK) == -1)
		return (printlog(WARNING, "Invalid .obj asset file."), 0);
	if (get_number_of_splits(param[2], ',') != 3)
		return (printlog(WARNING, "Invalid .obj asset position."), 0);
	if (get_number_of_splits(param[3], ',') != 3)
		return (printlog(WARNING, "Invalid .obj asset vector."), 0);
	if (get_number_of_splits(param[5], ',') != 3)
		return (printlog(WARNING, "Invalid .obj color."), 0);
	new_obj = gc_malloc(sizeof(t_obj));
	if (!new_obj)
		fatal_error(ERR_MEMORY, NULL);
	set_params(new_obj, param);
	add_obj(data->assets, new_obj);
	return (1);
}
