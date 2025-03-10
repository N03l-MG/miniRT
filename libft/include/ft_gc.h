/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:43:43 by nmonzon           #+#    #+#             */
/*   Updated: 2025/01/21 16:57:50 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GC_H
# define FT_GC_H

# include "libft.h"

typedef struct s_gc_node
{
	void				*ptr;
	size_t				size;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*head;
	size_t		total_allocations;
	size_t		total_memory;
}	t_gc;

void	gc_init(t_gc *g_gc);
void	*gc_malloc(size_t size, t_gc *g_gc);
void	gc_free(void *ptr, t_gc *g_gc);
void	gc_collect(t_gc *g_gc);

#endif
