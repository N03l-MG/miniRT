/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcolor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:27:01 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/19 09:18:40 by jgraf            ###   ########.fr       */
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

t_color	tcol_rgb(int r, int g, int b, int a)
{
	t_color	col;

	col.r = r;
	col.g = g;
	col.b = b;
	col.a = a;
	return (col);
}

uint8_t	tget_r(t_color col)
{
	return ((col.r >> 24) & 0xFF);
}

uint8_t	tget_g(t_color col)
{
	return ((col.g >> 16) & 0xFF);
}

uint8_t	tget_b(t_color col)
{
	return ((col.b >> 8) & 0xFF);
}

uint32_t	merge_tcolor(t_color col1, t_color col2, float val)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = col1.r + (col2.r - col1.r) * val;
	g = col1.g + (col2.g - col1.g) * val;
	b = col1.b + (col2.b - col1.b) * val;
	return (col_rgb(r, g, b, 0xFF));
}
