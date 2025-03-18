/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:27:01 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/18 11:27:13 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	col_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_r(uint32_t rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int	get_g(uint32_t rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int	get_b(uint32_t rgba)
{
	return ((rgba >> 8) & 0xFF);
}

uint32_t	merge_color(uint32_t col1, uint32_t col2, float val)
{
	int	r;
	int	g;
	int	b;

	r = get_r(col1) + (get_r(col2) - get_r(col1)) * val;
	g = get_g(col1) + (get_g(col2) - get_g(col1)) * val;
	b = get_b(col1) + (get_b(col2) - get_b(col1)) * val;
	return (col_rgb(r, g, b, 0xFF));
}
