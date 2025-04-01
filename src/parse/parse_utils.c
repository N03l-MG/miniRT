/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:45:39 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/31 12:45:20 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	These are the parsing utils. These are used to check the number of splits
*	possible for each section of the input (123,321,52 -> 3 split values for
*	a ',' delimiter).
*	As well as freeing split elements.
*	Because of the 42 norm rules I can not have more than 5 functions in a
*	single file, therefore I need to put assign_properties() in here.
*/

void	free_split(char **splt)
{
	int	i;

	i = 0;
	while (splt[i])
	{
		gc_free(splt[i]);
		i ++;
	}
	gc_free(splt);
}

int	get_number_of_split_elements(char **element)
{
	int	i;

	i = 0;
	while (element[i])
		i++;
	return (i);
}

int	get_number_of_splits(char *str, char c)
{
	int		i;
	int		nmb;

	i = 0;
	nmb = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			nmb++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (nmb);
}

char	*get_split_param(char *str, int i)
{
	char	**param;
	char	*trimmed;

	param = ft_split(str, ',');
	trimmed = ft_strtrim(param[i], " ");
	free_split(param);
	return (trimmed);
}

void	assign_properties(t_asset_node *current, void *asset, int type)
{
	if (type == AST_PLANE)
	{
		current->col = ((t_plane *)asset)->col;
		current->roughness = ((t_plane *)asset)->roughness;
		current->reflect = ((t_plane *)asset)->reflect;
	}
	else if (type == AST_SPHERE)
	{
		current->col = ((t_sphere *)asset)->col;
		current->roughness = ((t_sphere *)asset)->roughness;
		current->reflect = ((t_sphere *)asset)->reflect;
	}
	else if (type == AST_CYLINDER)
	{
		current->col = ((t_cylinder *)asset)->col;
		current->roughness = ((t_cylinder *)asset)->roughness;
		current->reflect = ((t_cylinder *)asset)->reflect;
	}
}
