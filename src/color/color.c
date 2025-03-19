/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:27:01 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/18 17:15:02 by jgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	These are functions for color creation or modification.
*	col_rgb()	creates a color from the given input.
*	get_r()		returns the value of the red channel of an existing color.
*	get_g()		returns the value of the green channel of an existing color.
*	get_b()		returns the value of the blue channel of an existing color.
*	merge_color()	returns a mixture of two colors based on a value.
*/

uint32_t	col_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint8_t	get_r(uint32_t rgba)
{
	return ((rgba >> 24) & 0xFF);
}

uint8_t	get_g(uint32_t rgba)
{
	return ((rgba >> 16) & 0xFF);
}

uint8_t	get_b(uint32_t rgba)
{
	return ((rgba >> 8) & 0xFF);
}

uint32_t	merge_color(uint32_t col1, uint32_t col2, float val)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = get_r(col1) + (get_r(col2) - get_r(col1)) * val;
	g = get_g(col1) + (get_g(col2) - get_g(col1)) * val;
	b = get_b(col1) + (get_b(col2) - get_b(col1)) * val;
	return (col_rgb(r, g, b, 0xFF));
}
