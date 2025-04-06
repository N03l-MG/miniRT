#include "miniRT.h"

static void count_elements(char *line, t_obj *obj)
{
	if (line[0] == 'v' && line[1] == ' ')
		obj->num_vertices++;
	else if (line[0] == 'v' && line[1] == 'n')
		obj->num_normals++;
	else if (line[0] == 'v' && line[1] == 't')
		obj->num_uvs++;
	else if (line[0] == 'f' && line[1] == ' ')
		obj->num_faces++;
}

static t_obj *allocate_obj_data(const char *filepath)
{
    t_obj   *obj;
    char    *line;
    int     fd;

    obj = gc_malloc(sizeof(t_obj));
    if (!obj)
        return (NULL);
    obj->num_vertices = 0;
    obj->num_normals = 0;
    obj->num_uvs = 0;
    obj->num_faces = 0;

    fd = open(filepath, O_RDONLY);
    if (fd < 0)
        return (NULL);
    
    line = get_next_line(fd);
    while (line)
    {
        count_elements(line, obj);
        gc_free(line);
        line = get_next_line(fd);
    }
    close(fd);

    obj->vertices = gc_malloc(sizeof(t_vector) * (obj->num_vertices + 1));
    obj->normals = gc_malloc(sizeof(t_vector) * (obj->num_normals + 1));
    obj->uvs = gc_malloc(sizeof(t_uv) * (obj->num_uvs + 1));
    obj->faces = gc_malloc(sizeof(Face) * (obj->num_faces + 1));

    if (!obj->vertices || !obj->normals || !obj->uvs || !obj->faces)
    {
        gc_free(obj->vertices);
        gc_free(obj->normals);
        gc_free(obj->uvs);
        gc_free(obj->faces);
        gc_free(obj);
        return (NULL);
    }
    return (obj);
}

static void parse_vertex(char *line, t_vector *vertex)
{
	char	**coords;

	coords = ft_split(line + 2, ' ');
	if (!coords || get_number_of_split_elements(coords) != 3)
		fatal_error(ERR_FILE, NULL);
	vertex->x = ft_atof(coords[0]);
	vertex->y = ft_atof(coords[1]);
	vertex->z = ft_atof(coords[2]);
	free_split(coords);
}

static void parse_face(char *line, Face *face)
{
	char	**vertices;
	char	**indices;
	int		i;

	vertices = ft_split(line + 2, ' ');
	if (!vertices || get_number_of_split_elements(vertices) != 3)
		fatal_error(ERR_FILE, NULL);

	i = 0;
	while (i < 3)
	{
		indices = ft_split(vertices[i], '/');
		if (!indices)
			fatal_error(ERR_FILE, NULL);
		
		face->v[i] = ft_atoi(indices[0]) - 1;
		face->vt[i] = (indices[1] && *indices[1]) ? ft_atoi(indices[1]) - 1 : -1;
		face->vn[i] = (indices[2] && *indices[2]) ? ft_atoi(indices[2]) - 1 : -1;
		
		free_split(indices);
		i++;
	}
	free_split(vertices);
}

static void parse_obj_file(t_obj *obj, const char *filepath)
{
    int     fd;
    char    *line;
    int     v_idx = 0;
    int     vn_idx = 0;
    int     vt_idx = 0;
    int     f_idx = 0;

    fd = open(filepath, O_RDONLY);
    if (fd < 0)
        fatal_error(ERR_FILE, NULL);

    // Initialize arrays with 0s
    ft_memset(obj->vertices, 0, sizeof(t_vector) * (obj->num_vertices + 1));
    ft_memset(obj->normals, 0, sizeof(t_vector) * (obj->num_normals + 1));
    ft_memset(obj->uvs, 0, sizeof(t_uv) * (obj->num_uvs + 1));
    ft_memset(obj->faces, 0, sizeof(Face) * (obj->num_faces + 1));

    line = get_next_line(fd);
    while (line)
    {
        if (line[0] == 'v' && line[1] == ' ' && v_idx < obj->num_vertices)
            parse_vertex(line, &obj->vertices[v_idx++]);
        else if (line[0] == 'v' && line[1] == 'n' && vn_idx < obj->num_normals)
            parse_vertex(line, &obj->normals[vn_idx++]);
        else if (line[0] == 'v' && line[1] == 't' && vt_idx < obj->num_uvs)
        {
            char **coords = ft_split(line + 3, ' ');
            if (coords && get_number_of_split_elements(coords) >= 2)
            {
                obj->uvs[vt_idx].u = ft_atof(coords[0]);
                obj->uvs[vt_idx].v = ft_atof(coords[1]);
                vt_idx++;
            }
            free_split(coords);
        }
        else if (line[0] == 'f' && line[1] == ' ' && f_idx < obj->num_faces)
            parse_face(line, &obj->faces[f_idx++]);
        
        gc_free(line);
        line = get_next_line(fd);
    }
    close(fd);
}

static void set_params(t_obj *obj, char **param)
{
    char **pos;
    char **rot;
    char **col;

    obj->roughness = DEFAULT_ROUGHNESS;
    obj->reflect = DEFAULT_REFLECT;
    obj->scale = 1.0f;  // Default scale

    pos = ft_split(param[2], ',');
    rot = ft_split(param[3], ',');
    col = ft_split(param[5], ',');

    if (!pos || !rot || !col)
        fatal_error(ERR_DATA, NULL);

    // Position
    obj->pos_x = ft_atof(pos[0]);
    obj->pos_y = ft_atof(pos[1]);
    obj->pos_z = ft_atof(pos[2]);
    
    // Rotation
    obj->rot_x = ft_atof(rot[0]);
    obj->rot_y = ft_atof(rot[1]);
    obj->rot_z = ft_atof(rot[2]);

    // Scale
    obj->scale = ft_atof(param[4]);

    // Color
    obj->col.r = ft_atoi(col[0]);
    obj->col.g = ft_atoi(col[1]);
    obj->col.b = ft_atoi(col[2]);

    // Material properties (optional)
    if (get_number_of_split_elements(param) >= 7)
        obj->roughness = ft_atof(param[6]);
    if (get_number_of_split_elements(param) >= 8)
        obj->reflect = ft_atof(param[7]);

    free_split(pos);
    free_split(rot);
    free_split(col);
}

static bool check_valid(t_obj *obj)
{
    if ((obj->rot_x < -360 || obj->rot_x > 360)
        || (obj->rot_y < -360 || obj->rot_y > 360)
        || (obj->rot_z < -360 || obj->rot_z > 360)
        || (obj->scale <= 0)
        || (obj->roughness < 0 || obj->roughness > 1)
        || (obj->reflect < 0 || obj->reflect > 1)
        || (obj->col.r < 0 || obj->col.r > 255)
        || (obj->col.g < 0 || obj->col.g > 255)
        || (obj->col.b < 0 || obj->col.b > 255))
        return (printlog(WARNING, "Invalid obj object parameters"), false);
    return (true);
}

static void add_obj(t_assets *assets, t_obj *new_obj)
{
    t_asset_node *new_node;
    t_asset_node *current;

    if (!check_valid(new_obj))
        return;
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
    printlog(LOG, "OBJ object setup successful.");
}

int parse_obj(t_scene_data *data, char **param)
{
    t_obj *new_obj;

    if (get_number_of_split_elements(param) < 6 || get_number_of_split_elements(param) > 8)
        return (printlog(WARNING, "Invalid obj configuration."), 0);
    if (get_number_of_splits(param[2], ',') != 3)
        return (printlog(WARNING, "Invalid obj object position."), 0);
    if (get_number_of_splits(param[3], ',') != 3)
        return (printlog(WARNING, "Invalid obj object rotation."), 0);
    if (get_number_of_splits(param[5], ',') != 3)
        return (printlog(WARNING, "Invalid obj color."), 0);

    // Try to open file first to validate it exists
    int fd = open(param[1], O_RDONLY);
    if (fd < 0)
        return (printlog(WARNING, "Invalid obj file path."), 0);
    close(fd);

    new_obj = allocate_obj_data(param[1]);
    if (!new_obj)
        fatal_error(ERR_MEMORY, NULL);
        
    parse_obj_file(new_obj, param[1]);
    set_params(new_obj, param);
    add_obj(data->assets, new_obj);
    return (1);
}
