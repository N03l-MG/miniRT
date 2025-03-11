/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:49:10 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/11 18:19:00 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	This is the main parsing function.
*	It reads through the file and calls an appropriate parsing function for
*	each element in the scene.
*	A corresponding instance of the object is added to a list or modified
*	directly in the data struct.
*/

void	parse_elements(t_scene_data *data, int fd)
{
	char	*line;

	(void)data;
	if (fd < 0)
		printf("Error! Could not open file.\n");
	while ((line = get_next_line(fd)))
	{
		if (ft_strncmp(line, "\n", 1) == 0)
			continue ;
		else if (ft_strncmp(line, "A", 1) == 0)
			printf("Ambiance\n");
		else if (ft_strncmp(line, "C", 1) == 0)
			printf("Camera\n");
		else if (ft_strncmp(line, "L", 1) == 0)
			printf("Light\n");
		else if (ft_strncmp(line, "sp", 2) == 0)
			printf("Sphere\n");
		else if (ft_strncmp(line, "cy", 2) == 0)
			printf("Cylinder\n");
		else if (ft_strncmp(line, "pl", 2) == 0)
			printf("Plane\n");
		free(line);
	}
}
