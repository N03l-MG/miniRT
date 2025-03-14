/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:27:01 by jgraf             #+#    #+#             */
/*   Updated: 2025/03/13 15:46:37 by jgraf            ###   ########.fr       */
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